#include "support/laser_program_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);

    // G96 S100 - CSS mode at 100 m/min surface speed
    CHECK(laser_block("G96S100") == Status_OK);
    CHECK(spindle_get(0)->rpm_mode == SpindleSpeedMode_CSS);
    NEAR(spindle_get(0)->hal->param->css.surface_speed, 100.0f);

    // G96 D5000 - Set max RPM limit
    CHECK(laser_block("G96D5000") == Status_OK);
    NEAR(spindle_get(0)->hal->param->css.max_rpm, 5000.0f);

    // G1 X20 F0.1 - Cutting move in CSS mode
    CHECK(laser_block("G1X20F0.1") == Status_OK);
    plan_block_t *block = plan_get_current_block();
    CHECK(block != NULL);
    CHECK(block->spindle.css != NULL);

    // G97 - Return to RPM mode
    CHECK(laser_block("G97") == Status_OK);
    CHECK(spindle_get(0)->rpm_mode == SpindleSpeedMode_RPM);

    return EXIT_SUCCESS;
}