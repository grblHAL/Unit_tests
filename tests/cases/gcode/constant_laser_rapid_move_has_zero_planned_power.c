#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_laser_program(false);
    CHECK(laser_block("G0X10M3S500") == Status_OK);
    plan_block_t *block = plan_get_current_block();
    CHECK(block != NULL);
    CHECK(block->condition.rapid_motion);
    NEAR(block->spindle.rpm, 0.0f);
    NEAR(laser_output_power, 0.0f);
    return EXIT_SUCCESS;
}
