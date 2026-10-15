#include "support/boot_spindle_feed_host.h"
int main(void)
{
    prepare_boot_spindle_feed("M3S100\nG95G1X1F1\n$G\n");
    CHECK(grbl_enter() == 0); check_boot_motion_completion();
    CHECK(hal.driver_cap.spindle_sync && settings.spindle.ppr == 100);
    CHECK(boot_feed_rpm_reads > 0 && boot_feed_angle_reads == 0);
    CHECK(boot_motor_position[X_AXIS] == 80 && boot_motor_pulses[X_AXIS] == 80);
    CHECK(sys.position[X_AXIS] == 80);
    NEAR(read_named_parameter("_units_per_rev"), 1);
    NEAR(read_named_parameter("_units_per_minute"), 0);
    CHECK(strstr(engine_output, " G95 ") != NULL);
    return EXIT_SUCCESS;
}
