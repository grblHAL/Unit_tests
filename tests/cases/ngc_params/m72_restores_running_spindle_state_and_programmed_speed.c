#include "support/laser_program_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_pwm_program_mode(Mode_Standard, false);
    CHECK(laser_block("M3S500") == Status_OK);
    CHECK(laser_output_state.on && !laser_output_state.ccw);
    CHECK(laser_block("M70") == Status_OK);
    CHECK(laser_block("M5") == Status_OK);
    CHECK(!laser_output_state.on);
    CHECK(laser_block("M72") == Status_OK);
    CHECK(laser_output_state.on && !laser_output_state.ccw);
    NEAR(laser_output_power, 500);
    NEAR(gc_state.spindle->rpm, 500);
    CHECK(gc_state.spindle->state.on);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
