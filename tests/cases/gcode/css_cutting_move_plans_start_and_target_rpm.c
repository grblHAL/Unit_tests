#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);
    CHECK(laser_block("G18G96M3S60D1000") == Status_OK);
    CHECK(laser_block("G1X20F100") == Status_OK);
    plan_block_t *block = plan_get_current_block();
    CHECK(block != NULL); CHECK(block->spindle.css != NULL);
    NEAR(block->spindle.rpm, 1000);
    NEAR(block->spindle.css->target_rpm, 60000.0f / (40.0f * (float)M_PI));
    NEAR(block->spindle.css->delta_rpm, block->spindle.css->target_rpm - 1000);
    CHECK(!block->condition.is_rpm_rate_adjusted);
    return EXIT_SUCCESS;
}
