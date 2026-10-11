#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_laser_program(false);
    CHECK(laser_block("M4S500") == Status_OK);
    CHECK(laser_block("G3X10I5F100") == Status_OK);
    unsigned count = 0;
    plan_block_t *block;
    while((block = plan_get_current_block())) {
        CHECK(block->condition.is_rpm_rate_adjusted);
        NEAR(block->spindle.rpm, 500.0f);
        count++;
        plan_discard_current_block();
    }
    CHECK(count > 1 && count < 64);
    NEAR(gc_state.position[X_AXIS], 10.0f);
    return EXIT_SUCCESS;
}
