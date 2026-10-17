#pragma once
#include "support/jog_motion_host.h"

/* Service emitted steps during generation/refill, then pause the simulated
   timer during a completed sender hold just as the driver does. */
static const char *held_program_text;
static unsigned held_program_index, held_program_lines, held_program_services;
static unsigned held_program_pause_ticks;
static bool held_program_full, held_program_sent, held_program_resumed, held_program_finished;
static bool held_program_drilling;
static bool held_program_followup_started;
static int32_t held_program_position[N_AXIS];
static void held_program_coolant(coolant_state_t state) { CHECK(state.mask == 0); }
static void held_program_reset(void) { }
static int32_t held_program_read(void)
{
    if(!held_program_text[held_program_index]) return SERIAL_NO_DATA;
    int32_t next = (uint8_t)held_program_text[held_program_index++];
    if(next == '\n') held_program_lines++;
    return next;
}
static void held_program_service(sys_state_t state)
{
    CHECK(++held_program_services < (held_program_drilling ? 2000000u : 200000u));
    if(state == STATE_CYCLE || state == STATE_HOLD) {
        if(state == STATE_CYCLE && held_program_lines == 2) held_program_followup_started = true;
        if(!held_program_sent && plan_check_full_buffer()) held_program_full = true;
        if(state == STATE_HOLD && sys.holding_state == Hold_Complete) {
            CHECK(!st_is_stepping());
            /* A synchronized peck may finish its current block before hold
               completes; a full-buffer curve must retain queued motion. */
            if(!held_program_drilling) CHECK(plan_get_current_block() != NULL);
            CHECK(held_program_lines == 1);
            if(held_program_pause_ticks++ == 0)
                memcpy(held_program_position, physical_position, sizeof(held_program_position));
            CHECK(memcmp(held_program_position, physical_position, sizeof(held_program_position)) == 0);
            if(held_program_pause_ticks == 32) {
                held_program_resumed = true;
                CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
            }
        } else {
            st_prep_buffer();
            stepper_driver_interrupt_handler();
            bool hold_point = held_program_drilling ? physical_position[Z_AXIS] <= -20 : axis_pulses[X_AXIS] >= 40;
            if(!held_program_sent && hold_point) {
                CHECK(held_program_lines == 1);
                if(!held_program_drilling) CHECK(held_program_full);
                held_program_sent = true;
                CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD));
            }
        }
    } else if(state == STATE_IDLE && held_program_resumed && held_program_followup_started && !plan_get_current_block()) {
        CHECK(plan_get_current_block() == NULL);
        held_program_finished = true;
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
    }
}
static void run_held_program(const char *program, float x, float y, float z)
{
    prepare_jog_motion();
    settings.arc_tolerance = .002f;
    sys.cold_start = false;
    sys.driver_started = true;
    stored_line_t empty = {0};
    for(unsigned i = 0; i < N_STARTUP_LINE; i++) settings_write_startup_line(i, empty);
    held_program_text = program;
    hal.stream.read = held_program_read;
    hal.coolant.set_state = held_program_coolant;
    hal.driver_reset = held_program_reset;
    grbl.on_execute_realtime = held_program_service;
    CHECK(!protocol_main_loop());
    CHECK(held_program_finished && held_program_sent && held_program_resumed);
    CHECK(held_program_pause_ticks == 32);
    if(held_program_drilling) CHECK(wake_calls >= 2);
    else CHECK(wake_calls == 2);
    float expected[N_AXIS] = {x, y, z};
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(physical_position[axis] == (int32_t)lroundf(expected[axis] * settings.axis[axis].steps_per_mm));
        CHECK(sys.position[axis] == physical_position[axis]);
        NEAR(gc_state.position[axis], expected[axis]);
    }
    CHECK(!sys.position_lost);
}
