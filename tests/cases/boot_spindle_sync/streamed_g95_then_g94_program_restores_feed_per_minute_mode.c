#include "support/boot_spindle_feed_host.h"
int main(void)
{
    prepare_boot_spindle_feed("M3S100\nG95G1X1F1\nG94G1X2F100\n$G\n");
    CHECK(grbl_enter() == 0); check_boot_motion_completion();
    CHECK(boot_feed_rpm_reads > 0);
    CHECK(boot_motor_position[X_AXIS] == 160 && boot_motor_pulses[X_AXIS] == 160);
    CHECK(sys.position[X_AXIS] == 160);
    NEAR(read_named_parameter("_units_per_rev"), 0);
    NEAR(read_named_parameter("_units_per_minute"), 1);
    NEAR(gc_state.feed_rate, 100);
    CHECK(strstr(engine_output, " G94 ") != NULL);
    return EXIT_SUCCESS;
}
