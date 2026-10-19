#include "support/laser_program_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, true);
    CHECK(laser_block("G96S100") == Status_OK);
    CHECK(gc_spindle_get(0)->rpm_mode == SpindleSpeedMode_CSS);
    NEAR(gc_spindle_get(0)->hal->param->css.surface_speed, 100000.0f);
    CHECK(laser_block("G96S100D5000") == Status_OK);
    NEAR(gc_spindle_get(0)->hal->param->css.max_rpm, 1000.0f);
    CHECK(laser_block("G1M3X20F0.1") == Status_OK);
    plan_block_t *block = plan_get_current_block();
    CHECK(block == NULL); /* Check mode validates CSS without queueing motion. */
    CHECK(laser_block("G97") == Status_OK);
    CHECK(gc_spindle_get(0)->rpm_mode == SpindleSpeedMode_RPM);

    return EXIT_SUCCESS;
}
