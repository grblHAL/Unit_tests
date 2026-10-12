#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_laser_program(true);
    CHECK(laser_block("M4S500") == Status_OK);
    CHECK(laser_block("G1X10F100M4S500") == Status_OK);
    CHECK(gc_state.is_rpm_rate_adjusted);
    NEAR(gc_state.position[X_AXIS], 10.0f);
    CHECK(laser_output_calls == 0);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
