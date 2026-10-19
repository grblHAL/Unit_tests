#include "support/laser_program_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);

    // G70 - Finishing cycle (requires Q subprogram)
    // G71 - Roughing cycle
    // G72 - Roughing cycle facing

    // These test parser dispatch to plugin interface
    CHECK(laser_block("G70P100Q200") == Status_OK);
    CHECK(laser_block("G71P100Q200U1W1D1F0.1") == Status_OK);
    CHECK(laser_block("G72P100Q200U1W1D1F0.1") == Status_OK);

    return EXIT_SUCCESS;
}