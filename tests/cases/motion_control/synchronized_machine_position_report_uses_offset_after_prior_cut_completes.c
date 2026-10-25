#include "support/canned_motion_host.h"

static coolant_state_t sync_report_coolant(void) { return (coolant_state_t){0}; }

int main(void)
{
    prepare_canned_motion();
    hal.coolant.get_state = sync_report_coolant;
    char mask[] = "289"; // Machine position, WCO and synchronization on offset changes.
    CHECK(settings_store_setting(Setting_StatusReportMask, mask) == Status_OK);
    CHECK(settings.status_report.machine_position && settings.status_report.sync_on_wco_change);
    CHECK(canned_block("G1X1F100") == Status_OK);
    CHECK(plan_get_current_block() != NULL && axis_pulses[X_AXIS] == 0);
    CHECK(canned_block("G92X0") == Status_OK);
    CHECK(plan_get_current_block() == NULL && physical_position[X_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 80);
    status_report_tracking_t tracking = {0};
    engine_output[0] = '\0';
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|MPos:1.000,0.000,0.000") != NULL);
    CHECK(strstr(engine_output, "|WCO:1.000,0.000,0.000") != NULL);
    CHECK(strstr(engine_output, "|WPos:") == NULL);
    execute_canned("G1X1");
    CHECK(physical_position[X_AXIS] == 160 && axis_pulses[X_AXIS] == 160);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None && !sys.abort);
    return EXIT_SUCCESS;
}
