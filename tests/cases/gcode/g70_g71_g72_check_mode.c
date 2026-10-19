#include "support/laser_program_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, true); // Check mode

    // G70 - Finishing cycle
    CHECK(laser_block("G70P100Q200") == Status_OK);

    // G71 - Roughing cycle
    CHECK(laser_block("G71P100Q200U1W1D1F0.1") == Status_OK);

    // G72 - Roughing cycle facing
    CHECK(laser_block("G72P100Q200U1W1D1F0.1") == Status_OK);

    // Check mode should not queue motion
    CHECK(plan_get_current_block() == NULL);

    return EXIT_SUCCESS;
}