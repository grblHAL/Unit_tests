#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);
    sys.position[X_AXIS] = 3200; sync_position();
    CHECK(laser_block("G18G96M3S60D1000") == Status_OK);
    CHECK(laser_block("G1X20F100") == Status_OK);
    plan_block_t *block = plan_get_current_block(); CHECK(block && block->spindle.css);
    CHECK(fabsf(block->spindle.rpm - 60000.0f / (80.0f * (float)M_PI)) < 0.01f);
    CHECK(fabsf(block->spindle.css->target_rpm - 60000.0f / (40.0f * (float)M_PI)) < 0.01f);
    CHECK(block->spindle.css->delta_rpm > 0);
    return EXIT_SUCCESS;
}
