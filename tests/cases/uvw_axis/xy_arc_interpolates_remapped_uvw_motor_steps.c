#include "support/extended_arc_motion_host.h"
int main(void)
{
    prepare_extended_arc_motion();
    observed_curve_axis = 0;
    queue_motion_program("G3X1Y1Z1U2V3W4J1F100");
    execute_motion_program();
    const int32_t expected[N_AXIS] = {80, 80, 80, 160, 240, 320};
    check_extended_arc_endpoint(expected);
    return EXIT_SUCCESS;
}
