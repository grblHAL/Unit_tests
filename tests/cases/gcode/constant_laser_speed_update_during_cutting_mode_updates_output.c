#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_laser_program(false);
    CHECK(laser_block("G1M3S500F100") == Status_OK);
    CHECK(laser_block("S250") == Status_OK);
    NEAR(laser_output_power, 250.0f);
    CHECK(laser_output_state.on);
    return EXIT_SUCCESS;
}
