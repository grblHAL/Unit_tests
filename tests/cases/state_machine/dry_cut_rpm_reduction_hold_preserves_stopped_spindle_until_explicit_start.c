#include "support/held_running_spindle_override_host.h"
int main(void)
{
    prepare_registered_running_spindle();
    char actions[] = "6";
    CHECK(settings_store_setting(Setting_HoldActions, actions) == Status_OK);
    CHECK(laser_block("M5") == Status_OK);
    unsigned writes = laser_output_calls;
    queue_motion_program("G1X20F100");
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned ticks = 0; ticks < 100; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    hold_motion();
    unsigned held = axis_pulses[X_AXIS];
    CHECK(laser_output_calls == writes && !laser_output_state.on);
    CHECK(!spindle_get(0)->param->option.restore_rpm);
    for(unsigned i = 0; i < 4; i++) {
        state_suspend_manager();
        CHECK(axis_pulses[X_AXIS] == held && !laser_output_state.on);
        CHECK(laser_last_driver_level == 0);
    }
    finish_registered_running_hold();
    CHECK(!laser_output_state.on && laser_last_driver_level == 0);
    CHECK(laser_output_calls == writes);
    CHECK(laser_block("M3S500") == Status_OK);
    CHECK(laser_output_state.on && laser_last_driver_level == 500);
    CHECK(axis_pulses[X_AXIS] == 1600 && state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
