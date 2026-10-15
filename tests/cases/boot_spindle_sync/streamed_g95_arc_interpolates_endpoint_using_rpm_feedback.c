#include "support/boot_spindle_feed_host.h"
int main(void)
{
    prepare_boot_spindle_feed("M3S100\nG95G3X1Y1J1F1\n");
    CHECK(grbl_enter() == 0); check_boot_motion_completion();
    CHECK(boot_feed_rpm_reads > 0 && boot_feed_angle_reads == 0);
    CHECK(boot_motor_position[X_AXIS] == 80 && boot_motor_position[Y_AXIS] == 80);
    CHECK(sys.position[X_AXIS] == 80 && sys.position[Y_AXIS] == 80);
    CHECK(boot_motor_pulses[X_AXIS] == 80 && boot_motor_pulses[Y_AXIS] == 80);
    return EXIT_SUCCESS;
}
