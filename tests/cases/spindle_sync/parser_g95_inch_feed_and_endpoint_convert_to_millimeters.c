#include "support/spindle_sync_motion_host.h"
int main(void)
{
    prepare_spindle_sync_motion();
    queue_motion_program("G20G95G1Z0.1F0.05");
    CHECK(plan_get_current_block()->condition.units_per_rev);
    NEAR(plan_get_current_block()->programmed_rate, 1.27f);
    execute_motion_program();
    CHECK(axis_pulses[Z_AXIS] == 203 && physical_position[Z_AXIS] == 203);
    NEAR(gc_state.position[Z_AXIS], 2.54f);
    CHECK(sync_rpm_reads > 0 && sync_angle_reads == 0 && sync_encoder_resets == 0);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
