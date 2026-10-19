#include "support/laser_program_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);

    // G76 threading cycle
    // G76 X10 Z-20 P1000 Q500 F1.0
    CHECK(laser_block("G76X10Z-20P1000Q500F1.0") == Status_OK);

    // G76 with multiple passes
    CHECK(laser_block("G76X10Z-20P1000Q500F1.0J2") == Status_OK);

    // G76 with spring passes
    CHECK(laser_block("G76X10Z-20P1000Q500F1.0K1") == Status_OK);

    // G80 - Cancel
    CHECK(laser_block("G80") == Status_OK);

    return EXIT_SUCCESS;
}