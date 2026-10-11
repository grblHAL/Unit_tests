#include "support/laser_stepper_host.h"
#include "check.h"

int main(void)
{
    prepare_laser_stepper();
    CHECK(laser_block("M3S500") == Status_OK);
    CHECK(laser_block("G1X10F100") == Status_OK);
    execute_motion_program();
    CHECK(laser_pwm_calls > 0);
    for(unsigned i = 0; i < laser_pwm_calls; i++) CHECK(laser_pwm_log[i] == 500);
    CHECK(laser_output_state.on);
    CHECK(physical_position[X_AXIS] == 800);
    return EXIT_SUCCESS;
}
