#include "support/boot_auto_report_host.h"

static bool checked;
static void check_live_report_controls(void)
{
    if(checked) return;
    checked = true;
    CHECK(sys.driver_started && settings.report_interval == 100);
    sys.rt_exec_state = 0;
    char disabled[] = "0";
    CHECK(settings_store_setting(Setting_AutoReportInterval, disabled) == Status_OK);
    CHECK(!sys.flags.auto_reporting && settings.report_interval == 0);
    advance_report_time(100);
    CHECK(!(sys.rt_exec_state & EXEC_STATUS_REPORT));
    char interval[] = "100";
    CHECK(settings_store_setting(Setting_AutoReportInterval, interval) == Status_OK);
    CHECK(!sys.flags.auto_reporting);
    CHECK(protocol_enqueue_realtime_command(CMD_AUTO_REPORTING_TOGGLE));
    CHECK(sys.flags.auto_reporting);
    advance_report_time(300);
    CHECK(!(sys.rt_exec_state & EXEC_STATUS_REPORT));
    sys.rt_exec_state = 0;
}

int main(void)
{
    boot_during_setup = configure_auto_reports;
    boot_before_read = check_live_report_controls;
    CHECK(grbl_enter() == 0);
    CHECK(checked && boot_release_calls == 1);
    CHECK(strstr(engine_output, "[GC:") != NULL);
    return EXIT_SUCCESS;
}
