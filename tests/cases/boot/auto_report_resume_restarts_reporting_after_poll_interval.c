#include "support/boot_auto_report_host.h"

int main(void)
{
    prepare_auto_reports();
    CHECK(protocol_enqueue_realtime_command(CMD_AUTO_REPORTING_TOGGLE));
    CHECK(!sys.flags.auto_reporting);
    advance_report_time(100);
    CHECK(!(sys.rt_exec_state & EXEC_STATUS_REPORT));
    CHECK(protocol_enqueue_realtime_command(CMD_AUTO_REPORTING_TOGGLE));
    CHECK(sys.flags.auto_reporting);
    advance_report_time(100);
    CHECK(!(sys.rt_exec_state & EXEC_STATUS_REPORT));
    advance_report_time(100);
    CHECK(sys.rt_exec_state & EXEC_STATUS_REPORT);
    return EXIT_SUCCESS;
}
