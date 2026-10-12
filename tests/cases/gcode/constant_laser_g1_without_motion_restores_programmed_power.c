#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_laser_program(false);
    CHECK(laser_block("G0M3S500") == Status_OK);
    NEAR(laser_output_power, 0.0f);
    CHECK(laser_block("G1F100") == Status_OK);
    NEAR(laser_output_power, 500.0f);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
