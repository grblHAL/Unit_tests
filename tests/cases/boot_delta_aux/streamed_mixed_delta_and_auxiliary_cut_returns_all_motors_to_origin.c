#include "support/boot_delta_stream_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_boot_delta_stream_motion("G91G1Z-0.5A1F100\nG1Z0.5A-1\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    for(unsigned motor = 0; motor < 3; motor++) {
        fprintf(stderr, "Delta motor%u position=%ld pulses=%u\n", motor,
            (long)boot_motor_position[motor], boot_motor_pulses[motor]);
        CHECK(sys.position[motor] == 0 && boot_motor_position[motor] == 0);
        CHECK(boot_motor_pulses[motor] == 10);
    }
    CHECK(sys.position[A_AXIS] == 0 && boot_motor_position[A_AXIS] == 0);
    CHECK(boot_motor_pulses[A_AXIS] == 160);
    NEAR(gc_state.position[A_AXIS], 0);
    CHECK(fabsf(gc_state.position[Z_AXIS] - delta_zero_angle_height()) < .03f);
    CHECK(fabsf(gc_state.position[X_AXIS]) < .03f && fabsf(gc_state.position[Y_AXIS]) < .03f);
    return EXIT_SUCCESS;
}
