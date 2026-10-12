#include "support/laser_stepper_host.h"
#include "check.h"

int main(void)
{
    prepare_pwm_stepper_mode(Mode_Lathe);
    CHECK(!spindle_get(0)->cap.laser);
    CHECK(laser_block("G18G96M3S60D1000") == Status_OK);
    CHECK(laser_block("G1X20F100") == Status_OK);
    execute_motion_program();
    CHECK(laser_pwm_calls > 1);
    bool reduced = false;
    for(unsigned i = 0; i < laser_pwm_calls; i++) {
        CHECK(laser_pwm_log[i] >= 477 && laser_pwm_log[i] <= 1000);
        reduced |= laser_pwm_log[i] < 700;
        if(i) CHECK(laser_pwm_log[i] <= laser_pwm_log[i-1]);
    }
    CHECK(reduced); CHECK(laser_output_state.on);
    CHECK(physical_position[X_AXIS] == 1600);
    return EXIT_SUCCESS;
}
