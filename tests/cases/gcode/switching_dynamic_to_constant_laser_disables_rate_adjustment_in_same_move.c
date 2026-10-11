#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_laser_program(false);
    CHECK(laser_block("M4S500") == Status_OK);
    CHECK(laser_block("G1X10F100M3") == Status_OK);
    plan_block_t *block = plan_get_current_block();
    CHECK(block != NULL);
    CHECK(!block->condition.is_rpm_rate_adjusted);
    NEAR(block->spindle.rpm, 500.0f);
    return EXIT_SUCCESS;
}
