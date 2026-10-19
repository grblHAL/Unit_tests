#include "support/laser_program_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);

    // G84 - Tapping cycle (right hand)
    CHECK(laser_block("G84X10Z-20R5F1.0") == Status_OK);

    // G88 - Tapping cycle (right hand, with dwell)
    CHECK(laser_block("G88X10Z-20R5F1.0P100") == Status_OK);

    // G80 - Cancel
    CHECK(laser_block("G80") == Status_OK);

    return EXIT_SUCCESS;
}