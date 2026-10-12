#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_laser_program(false);
    CHECK(laser_block("G0X10M4S500") == Status_OK);
    plan_block_t *block = plan_get_current_block();
    CHECK(block != NULL);
    CHECK(block->condition.rapid_motion);
    CHECK(!block->condition.is_rpm_rate_adjusted);
    NEAR(block->spindle.rpm, 0.0f);
    NEAR(gc_state.modal.spindle[0].rpm, 500.0f);
    return EXIT_SUCCESS;
}
