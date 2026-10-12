#include "support/laser_stepper_host.h"
#include "check.h"

int main(void)
{
    prepare_pwm_stepper_mode(Mode_Lathe);
    CHECK(!spindle_get(0)->cap.laser);
    CHECK(laser_block("G18G96M3S60D1000") == Status_OK);
    CHECK(laser_block("G1X-10F100") == Status_OK);
    execute_motion_program();
    NEAR(laser_output_power, 1000);
    for(unsigned i = 0; i < laser_pwm_calls; i++) CHECK(laser_pwm_log[i] == 1000);
    CHECK(physical_position[X_AXIS] == -800); CHECK(laser_output_state.on);
    return EXIT_SUCCESS;
}
