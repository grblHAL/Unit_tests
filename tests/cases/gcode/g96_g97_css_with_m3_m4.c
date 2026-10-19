#include "support/laser_program_host.h"
#include "spindle_control.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);

    // G96 S100 M3 - CSS mode CW at 100 m/min
    CHECK(laser_block("G96S100M3") == Status_OK);
    CHECK(spindle_get(0)->rpm_mode == SpindleSpeedMode_CSS);
    NEAR(spindle_get(0)->hal->param->css.surface_speed, 100.0f);
    CHECK(spindle_get(0)->param->state.ccw == false);

    // G96 S200 M4 - CSS mode CCW at 200 m/min
    CHECK(laser_block("G96S200M4") == Status_OK);
    NEAR(spindle_get(0)->hal->param->css.surface_speed, 200.0f);
    CHECK(spindle_get(0)->param->state.ccw == true);

    // G97 M3 - RPM mode CW
    CHECK(laser_block("G97M3S1000") == Status_OK);
    CHECK(spindle_get(0)->rpm_mode == SpindleSpeedMode_RPM);
    NEAR(spindle_get(0)->rpm, 1000.0f);
    CHECK(spindle_get(0)->param->state.ccw == false);

    return EXIT_SUCCESS;
}