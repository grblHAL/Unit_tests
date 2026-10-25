#include "support/paired_pwm_program_host.h"
#include "support/motion_program_host.h"
static void normal_spindle_pulse(stepper_t *stepper)
{
    CHECK(pair_output[0] == 600 && pair_calls[1] == 0);
    pulse_driver(stepper);
}
int main(void)
{
    pair_enable_secondary = false;
    prepare_paired_pwm_program_mode(Mode_Laser);
    hal.f_step_timer = 1000000;
    hal.stepper.enable = enable_motors;
    hal.stepper.go_idle = idle_driver;
    hal.stepper.wake_up = wake_driver;
    hal.stepper.cycles_per_tick = timer_cycles;
    hal.stepper.pulse_start = normal_spindle_pulse;
    st_reset();
    CHECK(spindle_get(0) && !spindle_get(0)->cap.laser);
    CHECK(spindle_get(1) == NULL);
    CHECK(spindle_program_block("S6000$0") == Status_OK);
    CHECK(spindle_program_block("M3$-1") == Status_OK);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
    CHECK(pair_output[0] == 600);
    NEAR(spindle_get(0)->param->rpm, 6000);
    CHECK(!actual_spindle_states[1].on && pair_calls[1] == 0);
    CHECK(spindle_program_block("G1X10F100") == Status_OK);
    plan_block_t *block = plan_get_current_block();
    CHECK(block && block->spindle.hal == spindle_get(0));
    CHECK(!block->condition.is_rpm_rate_adjusted);
    NEAR(block->spindle.rpm, 6000);
    execute_motion_program();
    CHECK(protocol_exec_rt_system());
    CHECK(physical_position[X_AXIS] == 800 && axis_pulses[X_AXIS] == 800);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(spindle_program_block("M5$-1") == Status_OK);
    CHECK(!actual_spindle_states[0].on && !actual_spindle_states[1].on);
    CHECK(pair_output[0] == 0);
    CHECK(pair_calls[1] == 0 && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
