#include "support/laser_stepper_host.h"
#include "check.h"

int main(void)
{
    prepare_laser_stepper();
    CHECK(laser_block("M4S500") == Status_OK);
    CHECK(laser_block("G0X10") == Status_OK);
    execute_motion_program();
    for(unsigned i = 0; i < laser_pwm_calls; i++) CHECK(laser_pwm_log[i] == 0);
    NEAR(laser_output_power, 0.0f);
    CHECK(physical_position[X_AXIS] == 800);
    return EXIT_SUCCESS;
}
