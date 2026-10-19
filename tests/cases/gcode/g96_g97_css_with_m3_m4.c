#include "support/laser_program_host.h"
#include "spindle_control.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);
    CHECK(laser_block("G96S100M3") == Status_OK);
    CHECK(gc_spindle_get(0)->rpm_mode == SpindleSpeedMode_CSS);
    NEAR(gc_spindle_get(0)->hal->param->css.surface_speed, 100000.0f);
    CHECK(spindle_get(0)->param->state.ccw == false);
    CHECK(laser_block("G96S200M4") == Status_OK);
    NEAR(gc_spindle_get(0)->hal->param->css.surface_speed, 200000.0f);
    CHECK(spindle_get(0)->param->state.ccw == true);
    CHECK(laser_block("G97M3S1000") == Status_OK);
    CHECK(gc_spindle_get(0)->rpm_mode == SpindleSpeedMode_RPM);
    NEAR(gc_spindle_get(0)->rpm, 1000.0f);
    CHECK(spindle_get(0)->param->state.ccw == false);

    return EXIT_SUCCESS;
}
