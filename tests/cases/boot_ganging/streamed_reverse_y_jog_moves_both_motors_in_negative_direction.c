#include "support/boot_stream_motion_host.h"
int main(void)
{
    prepare_boot_stream_motion("$J=G91Y-0.5F100\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(sys.position[1] == -40 && sys.position[3] == -40);
    CHECK(boot_motor_position[1] == -40 && boot_motor_position[3] == -40);
    CHECK(boot_motor_pulses[1] == 40 && boot_motor_pulses[3] == 40);
    CHECK(boot_motor_pulses[0] == 0 && boot_motor_pulses[2] == 0);
    NEAR(gc_state.position[1], -.5f);
    return EXIT_SUCCESS;
}
