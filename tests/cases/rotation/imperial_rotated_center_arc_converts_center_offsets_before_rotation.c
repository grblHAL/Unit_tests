#include "support/rotated_arc_motion_host.h"
int main(void)
{
    prepare_rotated_arc(90);
    queue_motion_program("G55G20G3X0.125Y0.125J0.125F4");
    check_rotated_arc_endpoint(-254, 254, 0);
    return EXIT_SUCCESS;
}
