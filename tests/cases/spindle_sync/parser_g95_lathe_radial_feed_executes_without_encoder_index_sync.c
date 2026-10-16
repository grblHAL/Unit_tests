#include "support/spindle_sync_motion_host.h"
int main(void)
{
    prepare_spindle_sync_motion();
    char lathe[] = "2";
    CHECK(settings_store_setting(Setting_Mode, lathe) == Status_OK);
    queue_motion_program("G95G1X1F1");
    CHECK(plan_get_current_block()->condition.units_per_rev);
    CHECK(!plan_get_current_block()->spindle.state.synchronized);
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(axis_pulses[Z_AXIS] == 0 && sync_rpm_reads > 0);
    CHECK(sync_angle_reads == 0 && sync_encoder_resets == 0);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
