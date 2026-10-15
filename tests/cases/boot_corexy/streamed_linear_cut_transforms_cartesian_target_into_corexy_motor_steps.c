#include "support/boot_stream_motion_host.h"
int main(void)
{
    prepare_boot_stream_motion("G91G1X0.5Y0.25Z0.25F100\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(sys.position[0] == 60 && boot_motor_position[0] == 60);
    CHECK(sys.position[1] == 20 && boot_motor_position[1] == 20);
    CHECK(sys.position[2] == 20 && boot_motor_position[2] == 20);
    NEAR(gc_state.position[0], 0.5f);
    NEAR(gc_state.position[1], 0.25f);
    NEAR(gc_state.position[2], 0.25f);
    return EXIT_SUCCESS;
}
