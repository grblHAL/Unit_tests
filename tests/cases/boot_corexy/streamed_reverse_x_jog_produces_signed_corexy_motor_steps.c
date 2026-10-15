#include "support/boot_stream_motion_host.h"
int main(void)
{
    prepare_boot_stream_motion("$J=G91X-0.5Y0.25F100\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(sys.position[0] == -20 && sys.position[1] == -60);
    CHECK(boot_motor_position[0] == -20 && boot_motor_position[1] == -60);
    CHECK(boot_motor_pulses[0] == 20 && boot_motor_pulses[1] == 60);
    NEAR(gc_state.position[0], -.5f);
    NEAR(gc_state.position[1], .25f);
    return EXIT_SUCCESS;
}
