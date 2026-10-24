#include "support/held_running_spindle_override_host.h"
int main(void)
{
    prepare_registered_running_spindle();
    CHECK(laser_block("M5") == Status_OK);
    CHECK(!laser_output_state.on && laser_last_driver_level == 0);
    unsigned first_dry_pwm = laser_pwm_calls;
    queue_motion_program("G1X20F100");
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned ticks = 0; ticks < 10000 && axis_pulses[X_AXIS] < 16; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    CHECK(axis_pulses[X_AXIS] >= 16 && axis_pulses[X_AXIS] < 1600);
    CHECK(state_get() == STATE_CYCLE);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_COARSE_PLUS));
    CHECK(protocol_exec_rt_system());
    CHECK(spindle_get(0)->param->override_pct == 110);
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(!laser_output_state.on && laser_last_driver_level == 0);
    for(unsigned i = first_dry_pwm; i < laser_pwm_calls; i++) CHECK(laser_pwm_log[i] == 0);
    CHECK(axis_pulses[X_AXIS] == 1600 && physical_position[X_AXIS] == 1600);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(laser_block("M3S500") == Status_OK);
    CHECK(laser_output_state.on && laser_last_driver_level == 550);
    CHECK(axis_pulses[X_AXIS] == 1600 && state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
