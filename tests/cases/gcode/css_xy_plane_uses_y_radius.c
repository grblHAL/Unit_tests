#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);
    CHECK(laser_block("G17G96M3S60D1000") == Status_OK);
    CHECK(laser_block("G1Y20F100") == Status_OK);
    plan_block_t *block = plan_get_current_block(); CHECK(block && block->spindle.css);
    CHECK(block->spindle.css->axis == Y_AXIS);
    CHECK(fabsf(block->spindle.css->target_rpm - 60000.0f / (40.0f * (float)M_PI)) < 0.01f);
    return EXIT_SUCCESS;
}
