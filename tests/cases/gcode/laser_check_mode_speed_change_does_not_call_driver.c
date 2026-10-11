#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_laser_program(true);
    CHECK(laser_block("M3S500") == Status_OK);
    CHECK(laser_output_calls == 0);
    CHECK(laser_block("S250") == Status_OK);
    NEAR(gc_state.modal.spindle[0].rpm, 250.0f);
    CHECK(laser_output_calls == 0);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
