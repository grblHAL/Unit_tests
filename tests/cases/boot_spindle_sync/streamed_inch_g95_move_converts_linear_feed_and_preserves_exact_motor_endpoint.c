#include "support/boot_spindle_feed_host.h"
int main(void)
{
    prepare_boot_spindle_feed("M3S100\nG20G95G1X0.5F0.01\n");
    CHECK(grbl_enter() == 0); check_boot_motion_completion();
    CHECK(boot_feed_rpm_reads > 0 && boot_feed_angle_reads == 0);
    CHECK(boot_motor_position[X_AXIS] == 1016 && boot_motor_pulses[X_AXIS] == 1016);
    CHECK(sys.position[X_AXIS] == 1016);
    NEAR(gc_state.feed_rate, 0.254f);
    CHECK(gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
