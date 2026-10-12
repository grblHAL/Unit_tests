#include "support/laser_stepper_host.h"
#include "check.h"

int main(void)
{
    prepare_pwm_stepper_mode(Mode_Lathe);
    sys.position[X_AXIS] = physical_position[X_AXIS] = 3200; sync_position();
    CHECK(laser_block("G18G96M3S60D1000") == Status_OK);
    CHECK(laser_block("G1X20F100") == Status_OK);
    execute_motion_program();
    CHECK(laser_pwm_calls > 1);
    bool increased = false;
    for(unsigned i = 0; i < laser_pwm_calls; i++) {
        CHECK(laser_pwm_log[i] >= 239 && laser_pwm_log[i] <= 478);
        increased |= laser_pwm_log[i] > 400;
        if(i) CHECK(laser_pwm_log[i] >= laser_pwm_log[i-1]);
    }
    CHECK(increased); CHECK(physical_position[X_AXIS] == 1600);
    CHECK(sys.position[X_AXIS] == 1600); CHECK(laser_output_state.on);
    return EXIT_SUCCESS;
}
