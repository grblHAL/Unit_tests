#include "support/extended_arc_motion_host.h"
int main(void)
{
    prepare_extended_arc_motion();
    observed_curve_axis = 0;
    queue_motion_program("G18G3X1Y2Z1A2B3C4U5V6I1F100");
    execute_motion_program();
    const int32_t expected[N_AXIS] = {80, 160, 80, 160, 240, 320, 400, 480};
    check_extended_arc_endpoint(expected);
    return EXIT_SUCCESS;
}
