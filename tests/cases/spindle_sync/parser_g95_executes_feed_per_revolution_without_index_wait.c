#include "support/spindle_sync_motion_host.h"
int main(void)
{
    prepare_spindle_sync_motion();
    queue_motion_program("G95G1Z1F1");
    CHECK(plan_get_current_block()->condition.units_per_rev);
    NEAR(plan_get_current_block()->programmed_rate, 1);
    execute_motion_program();
    CHECK(axis_pulses[Z_AXIS] == 80 && physical_position[Z_AXIS] == 80);
    CHECK(sync_rpm_reads > 0 && sync_angle_reads == 0 && sync_encoder_resets == 0);
    CHECK(hal.stepper.pulse_start == sync_motion_pulse);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
