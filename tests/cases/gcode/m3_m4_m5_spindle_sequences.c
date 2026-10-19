#include "support/laser_program_host.h"
#include "spindle_control.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);

    // M3 S1000 - Spindle CW
    CHECK(laser_block("M3S1000") == Status_OK);
    CHECK(spindle_get(0)->param->state.on == On);
    CHECK(spindle_get(0)->param->state.ccw == false);

    // M4 S2000 - Spindle CCW
    CHECK(laser_block("M4S2000") == Status_OK);
    CHECK(spindle_get(0)->param->state.ccw == true);

    // M5 - Stop
    CHECK(laser_block("M5") == Status_OK);
    CHECK(spindle_get(0)->param->state.on == false);

    // M3 S500 - Restart CW
    CHECK(laser_block("M3S500") == Status_OK);
    CHECK(spindle_get(0)->param->state.on == On);
    CHECK(spindle_get(0)->param->state.ccw == false);

    // M4 S1500 - Switch to CCW
    CHECK(laser_block("M4S1500") == Status_OK);
    CHECK(spindle_get(0)->param->state.ccw == true);

    // M5 - Stop
    CHECK(laser_block("M5") == Status_OK);
    CHECK(spindle_get(0)->param->state.on == false);

    return EXIT_SUCCESS;
}