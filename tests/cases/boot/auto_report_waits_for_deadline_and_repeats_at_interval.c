#include "support/boot_auto_report_host.h"

int main(void)
{
    prepare_auto_reports();
    advance_report_time(99);
    CHECK(!(sys.rt_exec_state & EXEC_STATUS_REPORT));
    advance_report_time(1);
    CHECK(sys.rt_exec_state & EXEC_STATUS_REPORT);
    sys.rt_exec_state = 0;
    advance_report_time(99);
    CHECK(!(sys.rt_exec_state & EXEC_STATUS_REPORT));
    advance_report_time(1);
    CHECK(sys.rt_exec_state & EXEC_STATUS_REPORT);
    return EXIT_SUCCESS;
}
