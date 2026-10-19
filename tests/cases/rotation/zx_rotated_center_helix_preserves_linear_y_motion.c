#include "support/rotated_arc_motion_host.h"
int main(void)
{
    prepare_rotated_arc(90);
    queue_motion_program("G55G18G3X1Y2Z1I1F100");
    check_rotated_arc_endpoint(80, 160, -80);
    return EXIT_SUCCESS;
}
