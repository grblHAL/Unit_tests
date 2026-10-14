#include "support/mpg_observer_host.h"
int main(void)
{
    prepare_mpg_stream();
    settings.status_report.overrides = true;
    grbl.on_rt_reports_added = NULL;
    CHECK(stream_mpg_register(&pendant_device,false,NULL));
    report_add_realtime(Report_Overrides);
    pendant_output[0] = 0;
    CHECK(stream_mpg_check_enable(CMD_STATUS_REPORT));
    engine_execute_tasks(STATE_IDLE);
    CHECK(strstr(pendant_output,"|Ov:") != NULL);
    return EXIT_SUCCESS;
}
