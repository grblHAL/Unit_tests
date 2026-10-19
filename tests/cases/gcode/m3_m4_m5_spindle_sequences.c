#include "support/laser_program_host.h"
#include "spindle_control.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);
    CHECK(laser_block("M3S1000") == Status_OK);
    CHECK(spindle_get(0)->param->state.on == On);
    CHECK(spindle_get(0)->param->state.ccw == false);
    CHECK(laser_block("M4S2000") == Status_OK);
    CHECK(spindle_get(0)->param->state.ccw == true);
    CHECK(laser_block("M5") == Status_OK);
    CHECK(spindle_get(0)->param->state.on == false);
    CHECK(laser_block("M3S500") == Status_OK);
    CHECK(spindle_get(0)->param->state.on == On);
    CHECK(spindle_get(0)->param->state.ccw == false);
    CHECK(laser_block("M4S1500") == Status_OK);
    CHECK(spindle_get(0)->param->state.ccw == true);
    CHECK(laser_block("M5") == Status_OK);
    CHECK(spindle_get(0)->param->state.on == false);

    return EXIT_SUCCESS;
}
