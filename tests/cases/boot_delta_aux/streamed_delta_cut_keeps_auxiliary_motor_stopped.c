#include "support/boot_delta_stream_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_boot_delta_stream_motion("G91G1Z-0.5F100\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    for(unsigned motor = 0; motor < 3; motor++) {
        CHECK(sys.position[motor] == 5 && boot_motor_position[motor] == 5);
        CHECK(boot_motor_pulses[motor] == 5);
    }
    CHECK(sys.position[A_AXIS] == 0 && boot_motor_position[A_AXIS] == 0);
    CHECK(boot_motor_pulses[A_AXIS] == 0);
    CHECK(fabsf(gc_state.position[Z_AXIS] - (delta_zero_angle_height() - .5f)) < .03f);
    return EXIT_SUCCESS;
}
