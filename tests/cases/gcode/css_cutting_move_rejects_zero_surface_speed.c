#include "support/laser_program_host.h"
#include "check.h"

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);
    CHECK(laser_block("G18G96M3S0D1000G1X20F100") == Status_GcodeSpindleNotRunning);
    CHECK(plan_get_current_block() == NULL);
    NEAR(gc_state.position[X_AXIS], 0);
    CHECK(laser_output_calls == 0);
    return EXIT_SUCCESS;
}
