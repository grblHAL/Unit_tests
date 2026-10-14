#include "support/mpg_observer_host.h"
int main(void)
{
    prepare_mpg_stream();
    settings.status_report.work_coord_offset = true;
    grbl.on_rt_reports_added = previous_reports;
    CHECK(stream_mpg_register(&pendant_device,false,NULL));
    CHECK(stream_mpg_check_enable(CMD_STATUS_REPORT)); engine_execute_tasks(STATE_IDLE);
    pendant_output[0] = 0;
    report_add_realtime(Report_WCO);
    CHECK(previous_calls == 1 && previous_flags.wco);
    pendant_output[0] = 0;
    CHECK(stream_mpg_check_enable(CMD_STATUS_REPORT));
    engine_execute_tasks(STATE_IDLE);
    CHECK(strstr(pendant_output,"|WCO:") != NULL);
    return EXIT_SUCCESS;
}
