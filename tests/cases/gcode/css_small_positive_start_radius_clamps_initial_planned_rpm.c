#include "support/laser_program_host.h"
int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);
    CHECK(laser_block("G18G92X1") == Status_OK);
    CHECK(laser_block("G96M3S60D1000") == Status_OK);
    CHECK(laser_block("G1X2F100") == Status_OK);
    plan_block_t *block = plan_get_current_block();
    CHECK(block != NULL && block->spindle.css != NULL);
    NEAR(block->spindle.css->tool_offset, -1);
    NEAR(block->spindle.rpm, 1000);
    NEAR(block->spindle.css->target_rpm, 1000);
    NEAR(block->spindle.css->delta_rpm, 0);
    return EXIT_SUCCESS;
}
