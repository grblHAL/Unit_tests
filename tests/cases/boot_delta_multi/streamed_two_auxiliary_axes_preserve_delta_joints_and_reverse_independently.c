#include "support/boot_delta_stream_motion_host.h"
#include "check.h"

int main(void)
{
    CHECK(N_AXIS == 5);
    prepare_boot_delta_stream_motion("G91G1A1B-0.5F100\nG1A-1B0.5\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    for(unsigned motor = 0; motor < 3; motor++) {
        CHECK(sys.position[motor] == 0 && boot_motor_position[motor] == 0);
        CHECK(boot_motor_pulses[motor] == 0);
    }
    CHECK(boot_motor_pulses[A_AXIS] == 160 && boot_motor_pulses[B_AXIS] == 80);
    for(unsigned axis = A_AXIS; axis <= B_AXIS; axis++) {
        CHECK(sys.position[axis] == 0 && boot_motor_position[axis] == 0);
        NEAR(gc_state.position[axis], 0);
    }
    CHECK(fabsf(gc_state.position[Z_AXIS] - delta_zero_angle_height()) < .03f);
    return EXIT_SUCCESS;
}
