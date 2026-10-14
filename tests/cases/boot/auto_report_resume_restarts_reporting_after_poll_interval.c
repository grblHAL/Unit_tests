#include "support/boot_auto_report_host.h"

int main(void)
{
    prepare_auto_reports();
    sys.flags.auto_reporting = false;
    advance_report_time(100);
    CHECK(!(sys.rt_exec_state & EXEC_STATUS_REPORT));
    sys.flags.auto_reporting = true;
    advance_report_time(100);
    CHECK(!(sys.rt_exec_state & EXEC_STATUS_REPORT));
    advance_report_time(100);
    CHECK(sys.rt_exec_state & EXEC_STATUS_REPORT);
    return EXIT_SUCCESS;
}
