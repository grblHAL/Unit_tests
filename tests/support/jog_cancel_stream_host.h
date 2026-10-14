#pragma once
#include "support/jog_motion_host.h"

/* A driver cancels queued input by returning ASCII_CAN to the main stream reader.
   Timer servicing models emitted pulses; it does not model motor mechanics. */
static const char *jog_stream_program = "$J=G21G91X10F100\n$J=G21G91X10F100\n";
static unsigned jog_stream_index, jog_cancel_calls, jog_service_calls;
static int jog_direction = 1;
static bool jog_program_inches_incremental;
static bool jog_can_pending, jog_cancel_sent, jog_stopped, jog_resume;
static bool jog_resume_started, jog_finished;
static int32_t jog_stop_position;
static float jog_stop_parser_position;
static unsigned jog_stop_pulses;

static void jog_cancel_input(void)
{
    jog_cancel_calls++;
    jog_stream_program = "";
    jog_stream_index = 0;
    jog_can_pending = true;
}
static int32_t jog_read_stream(void)
{
    if(jog_can_pending) {
        jog_can_pending = false;
        return ASCII_CAN;
    }
    if(jog_stream_program[jog_stream_index])
        return (uint8_t)jog_stream_program[jog_stream_index++];
    return SERIAL_NO_DATA;
}
static void jog_coolant_off(coolant_state_t state) { CHECK(state.mask == 0); }
static void jog_driver_reset(void) { }
static void jog_service_timer(sys_state_t state)
{
    CHECK(++jog_service_calls < 100000);
    if(state == STATE_JOG) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        if(!jog_cancel_sent && axis_pulses[X_AXIS] >= 40) {
            CHECK(wake_calls == 1);
            NEAR(gc_state.position[X_AXIS], 20 * jog_direction);
            jog_cancel_sent = true;
            CHECK(protocol_enqueue_realtime_command(CMD_JOG_CANCEL));
        }
        if(jog_stopped) jog_resume_started = true;
    } else if(state == STATE_IDLE && jog_cancel_sent && !jog_can_pending) {
        if(!jog_stopped) {
            jog_stopped = true;
            jog_stop_position = sys.position[X_AXIS];
            jog_stop_parser_position = gc_state.position[X_AXIS];
            jog_stop_pulses = axis_pulses[X_AXIS];
            CHECK(plan_get_current_block() == NULL);
            CHECK(!sys.suspend && !sys.step_control.execute_hold);
            if(jog_resume) {
                jog_stream_program = "$J=G21G91X1F100\n";
                jog_stream_index = 0;
                return;
            }
        } else if(jog_resume && !jog_resume_started)
            return;
        jog_finished = true;
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
    }
}
static void run_cancelled_jog(bool resume)
{
    prepare_jog_motion();
    if(jog_program_inches_incremental) {
        char modal[] = "G20G91";
        CHECK(gc_execute_block(modal) == Status_OK);
    }
    sys.cold_start = false;
    sys.driver_started = true;
    /* Empty startup records, as on an already initialized controller. */
    stored_line_t empty = {0};
    for(unsigned i = 0; i < N_STARTUP_LINE; i++) settings_write_startup_line(i, empty);
    hal.stream.read = jog_read_stream;
    hal.stream.cancel_read_buffer = jog_cancel_input;
    hal.coolant.set_state = jog_coolant_off;
    hal.driver_reset = jog_driver_reset;
    grbl.on_execute_realtime = jog_service_timer;
    jog_resume = resume;
    CHECK(!protocol_main_loop());
    CHECK(jog_finished && jog_stopped && jog_cancel_calls == 1);
    CHECK(jog_stop_pulses >= 40 && jog_stop_pulses < 800);
    CHECK(jog_stop_position == jog_direction * (int32_t)jog_stop_pulses);
    NEAR(jog_stop_parser_position, (float)jog_stop_position / settings.axis[X_AXIS].steps_per_mm);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(!sys.position_lost);
}

