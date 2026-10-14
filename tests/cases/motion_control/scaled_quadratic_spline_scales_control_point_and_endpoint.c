#include "support/spline_program_host.h"
int main(void)
{
    prepare_spline_program(400);
    CHECK(canned_block("G51X2Y3") == Status_OK);
    queue_motion_program("G5.1X10Y10I0J10F100");
    finish_spline_program(1600, 2400, 1800);
    return EXIT_SUCCESS;
}
