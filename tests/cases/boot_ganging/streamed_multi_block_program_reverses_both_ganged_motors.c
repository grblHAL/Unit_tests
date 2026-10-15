#include "support/boot_stream_motion_host.h"
int main(void)
{
    prepare_boot_stream_motion("G91G1Y0.5F100\nG1Y-0.25\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(sys.position[0] == 0 && boot_motor_position[0] == 0);
    CHECK(sys.position[1] == 20 && boot_motor_position[1] == 20);
    CHECK(sys.position[2] == 0 && boot_motor_position[2] == 0);
    CHECK(sys.position[3] == 20 && boot_motor_position[3] == 20);
    NEAR(gc_state.position[0], 0.0f);
    NEAR(gc_state.position[1], 0.25f);
    NEAR(gc_state.position[2], 0.0f);
    return EXIT_SUCCESS;
}
