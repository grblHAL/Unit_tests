#include "support/spindle_sync_motion_host.h"
int main(void)
{
    prepare_spindle_sync_motion();
    sync_motion_feedback.rpm = 0;
    unsigned reads_before = sync_rpm_reads;
    queue_motion_program("G95G0Z1");
    plan_block_t *block = plan_get_current_block();
    CHECK(block->condition.rapid_motion && !block->condition.units_per_rev);
    CHECK(!block->spindle.state.synchronized);
    execute_motion_program();
    CHECK(axis_pulses[Z_AXIS] == 80 && physical_position[Z_AXIS] == 80);
    CHECK(sync_rpm_reads == reads_before && sync_angle_reads == 0 && sync_encoder_resets == 0);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
