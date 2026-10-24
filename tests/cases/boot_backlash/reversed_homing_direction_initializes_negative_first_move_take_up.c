#include "support/boot_stream_motion_host.h"

int main(void)
{
    prepare_boot_stream_motion("$23=1\n$160=0.1\nG91\nG1X-1F100\nG1X1\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(settings.homing.dir_mask.mask == X_AXIS_BIT);
    NEAR(settings.axis[X_AXIS].backlash, .1f);
    CHECK(boot_motor_pulses[X_AXIS] == 176);
    CHECK(boot_motor_position[X_AXIS] == 0 && sys.position[X_AXIS] == 0);
    NEAR(gc_state.position[X_AXIS], 0);
    CHECK(boot_motor_pulses[Y_AXIS] == 0 && boot_motor_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
