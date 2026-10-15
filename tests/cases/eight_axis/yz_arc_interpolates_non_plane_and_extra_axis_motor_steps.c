#include "support/extended_arc_motion_host.h"
int main(void)
{
    prepare_extended_arc_motion();
    observed_curve_axis = 1;
    queue_motion_program("G19G3X2Y1Z1A2B3C4U5V6K1F100");
    execute_motion_program();
    const int32_t expected[N_AXIS] = {160, 80, 80, 160, 240, 320, 400, 480};
    check_extended_arc_endpoint(expected);
    return EXIT_SUCCESS;
}
