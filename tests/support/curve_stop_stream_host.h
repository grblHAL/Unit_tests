#pragma once
#include "support/jog_motion_host.h"

/* A sender stop arrives while a segmented curve is refilling the planner.
   The driver services actual step interrupts and cancels unread sender input. */
static const char *curve_program;
static unsigned curve_read_index, curve_service_calls, curve_cancel_calls, curve_line_reads;
static bool curve_can_pending, curve_stop_sent, curve_stopped, curve_finished;
static bool curve_resume_started;
static bool curve_full_seen;
static int32_t curve_stop_position[N_AXIS];
static float curve_stop_parser[N_AXIS];
static void curve_cancel_input(void)
{
    curve_cancel_calls++;
    curve_program = "";
    curve_read_index = 0;
    curve_can_pending = true;
}
static int32_t curve_read(void)
{
    if(curve_can_pending) {
        curve_can_pending = false;
        return ASCII_CAN;
    }
    if(!curve_program[curve_read_index]) return SERIAL_NO_DATA;
    int32_t next = (uint8_t)curve_program[curve_read_index++];
    if(next == '\n') curve_line_reads++;
    return next;
}
static void curve_coolant(coolant_state_t state) { CHECK(state.mask == 0); }
static void curve_driver_reset(void) { }
static void curve_service(sys_state_t state)
{
    CHECK(++curve_service_calls < 200000);
    if(state == STATE_CYCLE) {
        if(!curve_stop_sent && plan_check_full_buffer()) curve_full_seen = true;
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        if(!curve_stop_sent && axis_pulses[X_AXIS] >= 40) {
            CHECK(curve_line_reads == 1 && curve_full_seen);
            curve_stop_sent = true;
            CHECK(protocol_enqueue_realtime_command(CMD_STOP));
        }
        if(curve_stopped) curve_resume_started = true;
    } else if(state == STATE_IDLE && curve_stop_sent && !curve_can_pending) {
        if(!curve_stopped) {
            curve_stopped = true;
            CHECK(plan_get_current_block() == NULL && !st_is_stepping());
            for(unsigned axis = 0; axis < N_AXIS; axis++) {
                curve_stop_position[axis] = physical_position[axis];
                curve_stop_parser[axis] = gc_state.position[axis];
            }
            curve_program = "G91G1X1F100\n";
            curve_read_index = 0;
        } else if(curve_resume_started) {
            curve_finished = true;
            CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
        }
    }
}
static void run_stopped_curve(const char *program)
{
    prepare_jog_motion();
    settings.arc_tolerance = .002f;
    sys.cold_start = false;
    sys.driver_started = true;
    stored_line_t empty = {0};
    for(unsigned i = 0; i < N_STARTUP_LINE; i++) settings_write_startup_line(i, empty);
    curve_program = program;
    hal.stream.read = curve_read;
    hal.stream.cancel_read_buffer = curve_cancel_input;
    hal.coolant.set_state = curve_coolant;
    hal.driver_reset = curve_driver_reset;
    grbl.on_execute_realtime = curve_service;
    CHECK(!protocol_main_loop());
    CHECK(curve_finished && curve_stopped && curve_cancel_calls == 1);
    CHECK(axis_pulses[X_AXIS] >= 40);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == physical_position[axis]);
        NEAR(curve_stop_parser[axis], (float)curve_stop_position[axis] / settings.axis[axis].steps_per_mm);
        CHECK(physical_position[axis] == curve_stop_position[axis] + (axis == X_AXIS ? 80 : 0));
    }
    CHECK(!sys.position_lost);
}
