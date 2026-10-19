#include "support/boot_stream_motion_host.h"
int main(void)
{
    prepare_boot_stream_motion("G1X5Y5F100\nG28.1\nG1X10Y10\nG30.1\nG53G0X0Y0\nG30\nG28\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(sys.position[X_AXIS] == 400 && boot_motor_position[X_AXIS] == 400);
    CHECK(sys.position[Y_AXIS] == 400);
    CHECK(sys.position[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
