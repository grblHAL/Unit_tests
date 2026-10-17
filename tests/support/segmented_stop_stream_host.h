#pragma once
#include "support/jog_motion_host.h"

/* A sender stop arrives during planner refill or synchronized drilling.
   The driver services actual step interrupts and cancels unread sender input. */
static const char *sender_program;
static unsigned program_read_index, program_service_calls, program_cancel_calls, program_line_reads;
static bool program_can_pending, program_stop_sent, program_stopped, program_finished;
static bool program_resume_started;
static bool program_full_seen;
static bool program_stop_in_drill;
static int32_t program_stop_position[N_AXIS];
static float program_stop_parser[N_AXIS];
static void program_cancel_input(void)
{
    program_cancel_calls++;
    sender_program = "";
    program_read_index = 0;
    program_can_pending = true;
}
static int32_t program_read(void)
{
    if(program_can_pending) {
        program_can_pending = false;
        return ASCII_CAN;
    }
    if(!sender_program[program_read_index]) return SERIAL_NO_DATA;
    int32_t next = (uint8_t)sender_program[program_read_index++];
    if(next == '\n') program_line_reads++;
    return next;
}
static void program_coolant(coolant_state_t state) { CHECK(state.mask == 0); }
static void program_driver_reset(void) { }
static void program_service(sys_state_t state)
{
    CHECK(++program_service_calls < 200000);
    if(state == STATE_CYCLE) {
        if(!program_stop_sent && plan_check_full_buffer()) program_full_seen = true;
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        bool stop_point = program_stop_in_drill ? physical_position[Z_AXIS] <= -20 : axis_pulses[X_AXIS] >= 40;
        if(!program_stop_sent && stop_point) {
            CHECK(program_line_reads == 1);
            if(!program_stop_in_drill) CHECK(program_full_seen);
            program_stop_sent = true;
            CHECK(protocol_enqueue_realtime_command(CMD_STOP));
        }
        if(program_stopped) program_resume_started = true;
    } else if(state == STATE_IDLE && program_stop_sent && !program_can_pending) {
        if(!program_stopped) {
            program_stopped = true;
            CHECK(plan_get_current_block() == NULL && !st_is_stepping());
            for(unsigned axis = 0; axis < N_AXIS; axis++) {
                program_stop_position[axis] = physical_position[axis];
                program_stop_parser[axis] = gc_state.position[axis];
            }
            sender_program = "G91G1X1F100\n";
            program_read_index = 0;
        } else if(program_resume_started) {
            program_finished = true;
            CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
        }
    }
}
static void run_stopped_program(const char *program)
{
    prepare_jog_motion();
    settings.arc_tolerance = .002f;
    sys.cold_start = false;
    sys.driver_started = true;
    stored_line_t empty = {0};
    for(unsigned i = 0; i < N_STARTUP_LINE; i++) settings_write_startup_line(i, empty);
    sender_program = program;
    hal.stream.read = program_read;
    hal.stream.cancel_read_buffer = program_cancel_input;
    hal.coolant.set_state = program_coolant;
    hal.driver_reset = program_driver_reset;
    grbl.on_execute_realtime = program_service;
    CHECK(!protocol_main_loop());
    CHECK(program_finished && program_stopped && program_cancel_calls == 1);
    CHECK(axis_pulses[X_AXIS] >= 40);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        fprintf(stderr, "axis %u stopped steps=%ld parser=%.6f final steps=%ld\n", axis,
                (long)program_stop_position[axis], program_stop_parser[axis], (long)physical_position[axis]);
        CHECK(sys.position[axis] == physical_position[axis]);
        NEAR(program_stop_parser[axis], (float)program_stop_position[axis] / settings.axis[axis].steps_per_mm);
        CHECK(physical_position[axis] == program_stop_position[axis] + (axis == X_AXIS ? 80 : 0));
    }
    CHECK(!sys.position_lost);
}
