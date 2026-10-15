#include "support/boot_stream_motion_host.h"
int main(void)
{
    boot_restore_position = true;
    boot_hardware_position[0] = 800;
    boot_hardware_position[1] = 0;
    boot_hardware_position[2] = 0;
    prepare_boot_stream_motion("G91G1X0.25F100\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(sys.position[0] == 820 && boot_motor_position[0] == 820);
    CHECK(sys.position[1] == 0 && boot_motor_position[1] == 0);
    CHECK(sys.position[2] == 0 && boot_motor_position[2] == 0);
    NEAR(gc_state.position[0], 10.25f);
    NEAR(gc_state.position[1], 0.0f);
    NEAR(gc_state.position[2], 0.0f);
    return EXIT_SUCCESS;
}
