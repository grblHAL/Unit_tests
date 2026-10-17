#include "support/boot_homing_motion_host.h"
static bool requested, reported_during_motion;
static void homing_status_pulse(stepper_t *stepper)
{
    boot_homing_pulse(stepper);
    if(!requested && boot_motor_pulses[X_AXIS] == 20) {
        CHECK(protocol_enqueue_realtime_command(CMD_STATUS_REPORT));
        requested = true;
    } else if(requested && boot_motor_pulses[X_AXIS] > 20 &&
              boot_motor_pulses[X_AXIS] < 80 && strstr(engine_output, "<Home|"))
        reported_during_motion = true;
}
static void install_status_homing_driver(void)
{
    install_boot_homing_driver();
    hal.stepper.pulse_start = homing_status_pulse;
}
int main(void)
{
    prepare_boot_homing_motion();
    boot_during_init = install_status_homing_driver;
    CHECK(grbl_enter() == 0);
    CHECK(requested && reported_during_motion);
    CHECK(boot_motor_pulses[X_AXIS] == 110 && boot_motor_position[X_AXIS] == 70);
    CHECK(boot_motor_pulses[Y_AXIS] == 0 && boot_motor_pulses[Z_AXIS] == 0);
    CHECK(sys.homed.mask == X_AXIS_BIT);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
