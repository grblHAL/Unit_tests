#include "support/laser_program_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);

    // G76 X10 Z-20 P1000 Q500 F1.0 - Thread with P=1000 (depth*1000), Q=500 (spring passes)
    CHECK(laser_block("G76X10Z-20P1000Q500F1.0") == Status_OK);

    // G76 with J (thread angle)
    CHECK(laser_block("G76X10Z-20P1000Q500F1.0J30") == Status_OK);

    // G76 with K (thread depth)
    CHECK(laser_block("G76X10Z-20P1000Q500F1.0K0.5") == Status_OK);

    // G76 with H (infeed method)
    CHECK(laser_block("G76X10Z-20P1000Q500F1.0H1") == Status_OK);

    // G76 with E (taper)
    CHECK(laser_block("G76X10Z-20P1000Q500F1.0E0.1") == Status_OK);

    // G80 - Cancel
    CHECK(laser_block("G80") == Status_OK);

    return EXIT_SUCCESS;
}