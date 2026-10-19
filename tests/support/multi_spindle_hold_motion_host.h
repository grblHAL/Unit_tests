#pragma once
#include "support/multi_spindle_modal_host.h"
#include "support/hold_host.h"
static coolant_state_t multi_hold_coolant(void) { return (coolant_state_t){0}; }
static inline void start_multi_spindle_hold(bool secondary)
{
    modal_secondary_enabled = secondary;
    prepare_multi_spindle_modal_program();
    hal.coolant.get_state = multi_hold_coolant;
    hal.f_step_timer = 1000000;
    hal.stepper.enable = enable_motors;
    hal.stepper.go_idle = idle_driver;
    hal.stepper.wake_up = wake_driver;
    hal.stepper.cycles_per_tick = timer_cycles;
    hal.stepper.pulse_start = pulse_driver;
    settings.flags.restore_after_feed_hold = true;
    for(unsigned axis = 0; axis < N_AXIS; axis++) settings.axis[axis].acceleration = 36000;
    st_reset();
    CHECK(spindle_program_block("M3S3000$0") == Status_OK);
    if(secondary) CHECK(spindle_program_block("M4S7000$1") == Status_OK);
    else CHECK(!spindle_is_enabled(1) && gc_spindle_get(1)->hal == NULL);
    queue_motion_program("G1X20F100");
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned tick = 0; tick < 100; tick++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    hold_motion();
    CHECK(actual_spindle_states[0].on);
    NEAR(actual_spindle_rpm[0], 3000);
}
static inline void resume_multi_spindle_hold(void)
{
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(axis_pulses[X_AXIS] == 1600 && physical_position[X_AXIS] == 1600);
    CHECK(sys.position[X_AXIS] == 1600);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
}
