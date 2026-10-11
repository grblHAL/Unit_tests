#include "support/laser_stepper_host.h"
#include "check.h"

int main(void)
{
    prepare_laser_stepper();
    CHECK(laser_block("M4S500") == Status_OK);
    CHECK(laser_block("G1X10F100") == Status_OK);
    execute_motion_program();
    CHECK(laser_pwm_calls > 2);
    bool partial = false, full = false;
    for(unsigned i = 0; i < laser_pwm_calls; i++) {
        CHECK(laser_pwm_log[i] <= 500);
        partial |= laser_pwm_log[i] > 0 && laser_pwm_log[i] < 500;
        full |= laser_pwm_log[i] == 500;
    }
    CHECK(partial && full);
    CHECK(laser_pwm_log[laser_pwm_calls - 1] == 0);
    CHECK(physical_position[X_AXIS] == 800);
    return EXIT_SUCCESS;
}
