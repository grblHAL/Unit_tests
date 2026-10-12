#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);
    CHECK(laser_block("G18G96S60D1000") == Status_OK);
    unsigned outputs_before = laser_output_calls;
    CHECK(laser_block("G1X20F100") == Status_GcodeSpindleNotRunning);
    CHECK(plan_get_current_block() == NULL);
    NEAR(gc_state.position[X_AXIS], 0);
    CHECK(laser_output_calls == outputs_before);
    return EXIT_SUCCESS;
}
