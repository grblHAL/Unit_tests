#pragma once
#include "support/hold_host.h"

static spindle_state_t hold_spindle_output_state;
static float hold_spindle_output_rpm;
static unsigned hold_spindle_output_calls;
static int32_t hold_spindle_transition_position;
static void hold_spindle_set(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle == spindle_get(0));
    hold_spindle_output_state = state;
    hold_spindle_output_rpm = rpm;
    hold_spindle_output_calls++;
    hold_spindle_transition_position = physical_position[X_AXIS];
}
static spindle_state_t hold_spindle_get(spindle_ptrs_t *spindle)
{
    CHECK(spindle == spindle_get(0));
    return hold_spindle_output_state;
}
static bool hold_spindle_connected(void) { return true; }
static control_signals_t hold_spindle_controls(void) { return (control_signals_t){0}; }
static coolant_state_t hold_spindle_coolant(void) { return (coolant_state_t){0}; }
static inline void start_spindle_move(bool restore)
{
    prepare_motion_program();
    hal.stream.is_connected = hold_spindle_connected;
    hal.control.get_state = hold_spindle_controls;
    hal.coolant.get_state = hold_spindle_coolant;
    spindle_ptrs_t *spindle = spindle_get(0);
    spindle->cap.variable = spindle->cap.direction = true;
    spindle->rpm_min = 100;
    spindle->rpm_max = 12000;
    spindle->set_state = hold_spindle_set;
    spindle->get_state = hold_spindle_get;
    settings.flags.restore_after_feed_hold = restore;
    char command[] = "M3S5000";
    CHECK(gc_execute_block(command) == Status_OK);
    CHECK(hold_spindle_output_state.on);
    NEAR(hold_spindle_output_rpm, 5000);
    queue_motion_program("G1X20F100");
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned ticks = 0; ticks < 100; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
}
static inline void start_spindle_hold(bool restore)
{
    start_spindle_move(restore);
    hold_motion();
    CHECK(hold_spindle_output_state.on);
}
static inline void toggle_held_spindle(void)
{
    CHECK(state_get() == STATE_HOLD && sys.holding_state == Hold_Complete);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_STOP));
    CHECK(protocol_exec_rt_system());
    /* Same public service used by the core's suspend loop after realtime input. */
    state_suspend_manager();
    CHECK(state_get() == STATE_HOLD && sys.suspend);
}
static inline void resume_spindle_hold_to_endpoint(void)
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



