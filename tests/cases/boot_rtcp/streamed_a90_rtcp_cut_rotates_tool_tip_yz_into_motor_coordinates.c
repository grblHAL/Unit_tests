#include "support/boot_rtcp_stream_motion_host.h"
int main(void)
{
    boot_restore_position = true;
    boot_hardware_position[3] = 7200;
    prepare_zero_center_rtcp_stream_motion("M851\nG91G1Y0.25Z0.5F100\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    const int32_t expected[N_AXIS] = {0, -40, 20, 7200, 0};
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == expected[axis]);
        CHECK(boot_motor_position[axis] == expected[axis]);
    }
    NEAR(gc_state.position[0], 0.0f);
    NEAR(gc_state.position[1], 0.25f);
    NEAR(gc_state.position[2], 0.5f);
    CHECK(boot_motor_pulses[3] == 0 && boot_motor_pulses[4] == 0);
    return EXIT_SUCCESS;
}
