#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);
    CHECK(laser_block("G18G96M3S60D1000") == Status_OK);
    CHECK(laser_block("G1Z10F100") == Status_OK);
    plan_block_t *block = plan_get_current_block(); CHECK(block != NULL);
    NEAR(block->spindle.css->target_rpm, 1000); NEAR(block->spindle.css->delta_rpm, 0);
    return EXIT_SUCCESS;
}
