#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_laser_program(false);
    CHECK(laser_block("G0M3S500") == Status_OK);
    CHECK(laser_block("S250") == Status_OK);
    NEAR(laser_output_power, 0.0f);
    NEAR(gc_state.modal.spindle[0].rpm, 250.0f);
    return EXIT_SUCCESS;
}
