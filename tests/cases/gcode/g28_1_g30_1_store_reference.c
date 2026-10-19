#include "support/boot_stream_motion_host.h"
int main(void)
{
    prepare_boot_stream_motion("G1X5Y10Z-2F100\nG28.1\nG1X10Y20Z-3\nG30.1\nG53G0X0Y0Z0\nG28\nG30\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(sys.position[X_AXIS] == 800 && boot_motor_position[X_AXIS] == 800);
    CHECK(sys.position[Y_AXIS] == 1600);
    CHECK(sys.position[Z_AXIS] == -240);
    return EXIT_SUCCESS;
}
