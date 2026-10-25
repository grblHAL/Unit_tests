#include "support/wco_status_motion_host.h"

int main(void)
{
    prepare_wco_status_motion();
    char mask[] = "33"; // Machine position and WCO; offset changes remain nonblocking.
    CHECK(settings_store_setting(Setting_StatusReportMask, mask) == Status_OK);
    CHECK(settings.status_report.machine_position && settings.status_report.work_coord_offset);
    CHECK(!settings.status_report.sync_on_wco_change);
    queue_motion_program("G1X1F100");
    wco_block("G92X0");
    CHECK(axis_pulses[X_AXIS] == 0 && physical_position[X_AXIS] == 0);
    queue_motion_program("G1X1");
    expected_work_positions[0] = "|MPos:0.500,0.000,0.000";
    expected_work_positions[1] = "|MPos:1.500,0.000,0.000";
    expected_work_offsets[0] = "|WCO:0.000,0.000,0.000";
    expected_work_offsets[1] = "|WCO:1.000,0.000,0.000";
    run_two_offset_moves(0, 1);
    CHECK(wco_status_samples == 2 && !sys.abort && sys.alarm == Alarm_None);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
