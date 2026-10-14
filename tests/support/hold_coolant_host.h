#pragma once
#include "support/hold_host.h"
static coolant_state_t held_coolant_output;
static unsigned held_coolant_calls;
static int32_t held_coolant_transition_position;
static coolant_state_t held_coolant_get(void) { return held_coolant_output; }
static void held_coolant_set(coolant_state_t state)
{
    held_coolant_output = state;
    held_coolant_calls++;
    held_coolant_transition_position = physical_position[X_AXIS];
}
static control_signals_t held_coolant_controls(void) { return (control_signals_t){0}; }
static bool held_coolant_connected(void) { return true; }
static inline void start_coolant_hold(bool restore, bool mist)
{
    prepare_motion_program();
    hal.coolant.get_state = held_coolant_get;
    hal.coolant.set_state = held_coolant_set;
    hal.coolant_cap.flood = hal.coolant_cap.mist = true;
    hal.control.get_state = held_coolant_controls;
    hal.stream.is_connected = held_coolant_connected;
    settings.flags.restore_after_feed_hold = restore;
    char flood[] = "M8";
    CHECK(gc_execute_block(flood) == Status_OK);
    if(mist) {
        char mist_command[] = "M7";
        CHECK(gc_execute_block(mist_command) == Status_OK);
    }
    CHECK(held_coolant_output.flood && held_coolant_output.mist == mist);
    queue_motion_program("G1X20F100");
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned ticks = 0; ticks < 100; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    hold_motion();
}
static inline void toggle_hold_coolant(uint8_t command)
{
    CHECK(protocol_enqueue_realtime_command(command));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_HOLD && sys.suspend);
}
static inline void resume_coolant_hold(void)
{
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_CYCLE && !sys.suspend);
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE);
    CHECK(axis_pulses[X_AXIS] == 1600);
    CHECK(sys.position[X_AXIS] == physical_position[X_AXIS]);
    CHECK(plan_get_current_block() == NULL);
}
