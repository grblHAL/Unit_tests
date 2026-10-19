#include "support/rotated_arc_motion_host.h"
int main(void)
{
    prepare_rotated_arc(-90);
    queue_motion_program("G55G3X1Y1J1F100");
    check_rotated_arc_endpoint(80, -80, 0);
    return EXIT_SUCCESS;
}
