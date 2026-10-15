#include "support/boot_stream_motion_host.h"
int main(void)
{
    boot_restore_position = true;
    boot_hardware_position[0] = 10000;
    boot_hardware_position[1] = 10000;
    boot_hardware_position[2] = 0;
    prepare_boot_stream_motion("$J=G91X0.25F100\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(sys.position[0] == 10016 && boot_motor_position[0] == 10016);
    CHECK(sys.position[1] == 9984 && boot_motor_position[1] == 9984);
    CHECK(sys.position[2] == 0 && boot_motor_position[2] == 0);
    NEAR(gc_state.position[0], 100.25f);
    /* A completed jog can resync from quantized cable counters. */
    CHECK(fabsf(gc_state.position[1] - 75.0f) < .01f);
    NEAR(gc_state.position[2], 0.0f);
    return EXIT_SUCCESS;
}
