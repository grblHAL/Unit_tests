#include "support/rotated_arc_motion_host.h"
int main(void)
{
    prepare_rotated_arc(90);
    queue_motion_program("G55G19G3X2Y1Z1K1F100");
    check_rotated_arc_endpoint(160, -80, 80);
    return EXIT_SUCCESS;
}
