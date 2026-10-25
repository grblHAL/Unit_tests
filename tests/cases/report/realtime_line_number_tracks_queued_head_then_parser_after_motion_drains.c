#include "support/wco_status_motion_host.h"
static void check_line_number(const char *expected)
{
    status_report_tracking_t tracking = {0};
    engine_output[0] = '\0';
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, expected) != NULL);
}
int main(void)
{
    prepare_wco_status_motion();
    char mask[] = "4";
    CHECK(settings_store_setting(Setting_StatusReportMask, mask) == Status_OK);
    queue_motion_program("N42G1X1F100");
    queue_motion_program("N43X2");
    CHECK(gc_state.line_number == 43 && plan_get_current_block()->line_number == 42);
    check_line_number("|Ln:42");
    execute_motion_program();
    CHECK(protocol_exec_rt_system());
    CHECK(physical_position[X_AXIS] == 160 && axis_pulses[X_AXIS] == 160);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(plan_get_current_block() == NULL);
    check_line_number("|Ln:43");
    wco_block("G90");
    status_report_tracking_t tracking = {0};
    engine_output[0] = '\0';
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(gc_state.line_number == 0 && strstr(engine_output, "|Ln:") == NULL);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
