#include "support/registered_spindle_hold_observer_host.h"
int main(void)
{
    prepare_pwm_stepper_mode(Mode_Standard);
    sys.cold_start = false;
    sys.driver_started = true;
    hal.coolant.get_state = held_no_coolant;
    char hold_actions[] = "4";
    CHECK(settings_store_setting(Setting_HoldActions, hold_actions) == Status_OK);
    CHECK(settings.flags.set_rpm_0_during_hold && !settings.flags.restore_after_feed_hold);
    CHECK(laser_block("M3S500G1X20F100") == Status_OK);
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned tick = 0; tick < 100; tick++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    hold_motion();
    CHECK(laser_output_state.on);
    NEAR(laser_output_power, spindle_get(0)->rpm_min);
    CHECK(!spindle_get(0)->param->option.restore_rpm);
    int32_t stopped = physical_position[X_AXIS];
    toggle_registered_held_spindle();
    CHECK(!laser_output_state.on && sys.override.spindle_stop.enabled);
    CHECK(physical_position[X_AXIS] == stopped);
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(physical_position[X_AXIS] == 1600 && sys.position[X_AXIS] == 1600);
    CHECK(axis_pulses[X_AXIS] == 1600 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(!laser_output_state.on);
    NEAR(laser_output_power, 0);
    CHECK(!gc_spindle_get(0)->state.on && sys.override.spindle_stop.value == 0);
    NEAR(gc_spindle_get(0)->rpm, 0);
    return EXIT_SUCCESS;
}
