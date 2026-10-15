#include "support/mpg_stream_host.h"
int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    primary_output[0] = pendant_output[0] = '\0';
    settings.status_report.work_coord_offset = true;
    settings.status_report.overrides = true;
    CHECK(stream_mpg_check_enable(CMD_STATUS_REPORT_ALL));
    CHECK(pendant_output[0] == '\0');
    engine_execute_tasks(STATE_IDLE);
    CHECK(strncmp(pendant_output, "<Idle", 5) == 0);
    CHECK(strstr(pendant_output, "|WCO:") != NULL);
    CHECK(strstr(pendant_output, "|Ov:100,100,100") != NULL);
    CHECK(primary_output[0] == '\0');
    return EXIT_SUCCESS;
}
