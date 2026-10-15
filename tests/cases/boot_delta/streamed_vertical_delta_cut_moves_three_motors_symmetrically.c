#include "support/boot_delta_stream_motion_host.h"
int main(void)
{
    prepare_boot_delta_stream_motion("G91G1Z-0.5F100\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    for(unsigned axis = 0; axis < 3; axis++) {
        CHECK(sys.position[axis] == 5);
        CHECK(boot_motor_position[axis] == 5);
        CHECK(boot_motor_pulses[axis] == 5);
    }
    CHECK(fabsf(gc_state.position[X_AXIS]) < .001f && fabsf(gc_state.position[Y_AXIS]) < .001f);
    /* Quantized joint counters allow a small Cartesian rounding difference. */
    CHECK(fabsf(gc_state.position[Z_AXIS] - (delta_zero_angle_height() - 0.5f)) < .03f);
    return EXIT_SUCCESS;
}
