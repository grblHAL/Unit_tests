#pragma once
#include "support/jog_motion_host.h"

/* Service emitted steps during generation/refill, then pause the simulated
   timer during a completed sender hold just as the driver does. */
static const char *held_curve_program;
static unsigned held_curve_index, held_curve_lines, held_curve_services;
static unsigned held_curve_pause_ticks;
static bool held_curve_full, held_curve_sent, held_curve_resumed, held_curve_finished;
static int32_t held_curve_position[N_AXIS];
static void held_curve_coolant(coolant_state_t state) { CHECK(state.mask == 0); }
static void held_curve_reset(void) { }
static int32_t held_curve_read(void)
{
    if(!held_curve_program[held_curve_index]) return SERIAL_NO_DATA;
    int32_t next = (uint8_t)held_curve_program[held_curve_index++];
    if(next == '\n') held_curve_lines++;
    return next;
}
static void held_curve_service(sys_state_t state)
{
    CHECK(++held_curve_services < 200000);
    if(state == STATE_CYCLE || state == STATE_HOLD) {
        if(!held_curve_sent && plan_check_full_buffer()) held_curve_full = true;
        if(state == STATE_HOLD && sys.holding_state == Hold_Complete) {
            CHECK(plan_get_current_block() != NULL && !st_is_stepping());
            CHECK(held_curve_lines == 1);
            if(held_curve_pause_ticks++ == 0)
                memcpy(held_curve_position, physical_position, sizeof(held_curve_position));
            CHECK(memcmp(held_curve_position, physical_position, sizeof(held_curve_position)) == 0);
            if(held_curve_pause_ticks == 32) {
                held_curve_resumed = true;
                CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
            }
        } else {
            st_prep_buffer();
            stepper_driver_interrupt_handler();
            if(!held_curve_sent && axis_pulses[X_AXIS] >= 40) {
                CHECK(held_curve_full && held_curve_lines == 1);
                held_curve_sent = true;
                CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD));
            }
        }
    } else if(state == STATE_IDLE && held_curve_resumed && held_curve_lines == 2) {
        CHECK(plan_get_current_block() == NULL);
        held_curve_finished = true;
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
    }
}
static void run_held_curve(const char *program, float x, float y, float z)
{
    prepare_jog_motion();
    settings.arc_tolerance = .002f;
    sys.cold_start = false;
    sys.driver_started = true;
    stored_line_t empty = {0};
    for(unsigned i = 0; i < N_STARTUP_LINE; i++) settings_write_startup_line(i, empty);
    held_curve_program = program;
    hal.stream.read = held_curve_read;
    hal.coolant.set_state = held_curve_coolant;
    hal.driver_reset = held_curve_reset;
    grbl.on_execute_realtime = held_curve_service;
    CHECK(!protocol_main_loop());
    CHECK(held_curve_finished && held_curve_sent && held_curve_resumed);
    CHECK(held_curve_pause_ticks == 32 && wake_calls == 2);
    float expected[N_AXIS] = {x, y, z};
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(physical_position[axis] == (int32_t)lroundf(expected[axis] * settings.axis[axis].steps_per_mm));
        CHECK(sys.position[axis] == physical_position[axis]);
        NEAR(gc_state.position[axis], expected[axis]);
    }
    CHECK(!sys.position_lost);
}
