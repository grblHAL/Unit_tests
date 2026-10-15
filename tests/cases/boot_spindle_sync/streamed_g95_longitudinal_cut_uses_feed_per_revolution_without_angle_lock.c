#include "support/boot_spindle_feed_host.h"
int main(void)
{
    prepare_boot_spindle_feed("M3S100\nG95G1Z1F1\n");
    CHECK(grbl_enter() == 0); check_boot_motion_completion();
    CHECK(boot_feed_rpm_reads > 0 && boot_feed_angle_reads == 0);
    CHECK(boot_motor_position[Z_AXIS] == 80 && boot_motor_pulses[Z_AXIS] == 80);
    CHECK(sys.position[Z_AXIS] == 80 && boot_motor_pulses[X_AXIS] == 0);
    NEAR(read_named_parameter("_units_per_rev"), 1);
    return EXIT_SUCCESS;
}
