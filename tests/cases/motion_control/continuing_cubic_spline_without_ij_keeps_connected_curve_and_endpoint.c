#include "support/spline_program_host.h"
int main(void)
{
    prepare_spline_program(1150);
    queue_motion_program("G5X10Y10I0J10P-10Q0F100");
    queue_motion_program("G5X20Y20P-10Q0");
    /* Joined second cubic at t=1/4 gives x=14.375,y=11.5625 mm. */
    finish_spline_program(1600, 1600, 925);
    return EXIT_SUCCESS;
}
