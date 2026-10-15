#include "support/boot_stream_motion_host.h"
int main(void)
{
    prepare_boot_stream_motion("G91G1X0.5F100\nG20\nG1X0.01F10\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(sys.position[0] == 60 && boot_motor_position[0] == 60);
    CHECK(sys.position[1] == 60 && boot_motor_position[1] == 60);
    CHECK(sys.position[2] == 0 && boot_motor_position[2] == 0);
    NEAR(gc_state.position[0], 0.754f);
    NEAR(gc_state.position[1], 0.0f);
    NEAR(gc_state.position[2], 0.0f);
    CHECK(gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
