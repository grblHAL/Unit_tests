#include "support/boot_stream_motion_host.h"
int main(void)
{
    prepare_boot_stream_motion("$J=G91Y0.5F100\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(sys.position[0] == 0 && boot_motor_position[0] == 0);
    CHECK(sys.position[1] == 40 && boot_motor_position[1] == 40);
    CHECK(sys.position[2] == 0 && boot_motor_position[2] == 0);
    CHECK(sys.position[3] == 40 && boot_motor_position[3] == 40);
    NEAR(gc_state.position[0], 0.0f);
    NEAR(gc_state.position[1], 0.5f);
    NEAR(gc_state.position[2], 0.0f);
    return EXIT_SUCCESS;
}
