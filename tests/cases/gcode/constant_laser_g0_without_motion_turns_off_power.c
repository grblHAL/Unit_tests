#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_laser_program(false);
    CHECK(laser_block("G1M3S500F100") == Status_OK);
    NEAR(laser_output_power, 500.0f);
    CHECK(laser_block("G0") == Status_OK);
    NEAR(laser_output_power, 0.0f);
    NEAR(gc_state.modal.spindle[0].rpm, 500.0f);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
