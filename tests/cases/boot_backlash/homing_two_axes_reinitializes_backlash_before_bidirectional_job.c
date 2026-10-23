#include "support/boot_stream_motion_host.h"
static const char homing_prefix[] = "$160=0.1\n$161=0.1\n$HX\n$HY\n";
static unsigned observed_home;
static void install_homing_job(void)
{
    install_boot_motion_driver();
    settings.homing.flags.enabled = true;
    settings.homing.flags.init_lock = false;
    settings_write_global();
}
static void observe_completed_homing(void)
{
    if(boot_reads == strlen(homing_prefix)) {
        CHECK(sys.homed.mask == (X_AXIS_BIT | Y_AXIS_BIT));
        CHECK(boot_motor_position[X_AXIS] == 70 && boot_motor_position[Y_AXIS] == 110);
        CHECK(boot_motor_pulses[X_AXIS] == 110 && boot_motor_pulses[Y_AXIS] == 150);
        CHECK(sys.position[X_AXIS] == -10 && sys.position[Y_AXIS] == -10);
        observed_home++;
        boot_before_read = NULL;
    }
}
int main(void)
{
    prepare_boot_stream_motion("$160=0.1\n$161=0.1\n$HX\n$HY\nG91\nG1X-1Y-1F100\nG1X1Y1\n");
    boot_during_init = install_homing_job;
    boot_before_read = observe_completed_homing;
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(observed_home == 1);
    CHECK(sys.homed.mask == (X_AXIS_BIT | Y_AXIS_BIT));
    NEAR(settings.axis[X_AXIS].backlash, .1f);
    NEAR(settings.axis[Y_AXIS].backlash, .1f);
    CHECK(sys.position[X_AXIS] == -10 && sys.position[Y_AXIS] == -10);
    NEAR(gc_state.position[X_AXIS], -.125f);
    NEAR(gc_state.position[Y_AXIS], -.125f);
    CHECK(boot_motor_position[X_AXIS] == 78 && boot_motor_position[Y_AXIS] == 118);
    CHECK(boot_motor_pulses[X_AXIS] == 278 && boot_motor_pulses[Y_AXIS] == 318);
    CHECK(boot_motor_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
