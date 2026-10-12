#include "support/spindle_sync_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_sync_motion(); queue_spindle_sync_line(10,true); execute_motion_program();
    CHECK(hal.stepper.pulse_start==sync_motion_pulse); CHECK(sync_rpm_reads>0); CHECK(sync_angle_reads==0);
    CHECK(axis_pulses[Z_AXIS]==800); CHECK(physical_position[Z_AXIS]==800);
    return EXIT_SUCCESS;
}
