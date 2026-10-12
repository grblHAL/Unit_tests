#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    settings.mpg_report_interval = 100;
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    primary_output[0] = pendant_output[0] = '\0';
    engine_ticks = 1999;
    engine_execute_tasks(STATE_IDLE);
    CHECK(pendant_output[0] == '\0');
    engine_ticks = 2000;
    engine_execute_tasks(STATE_IDLE);
    CHECK(strncmp(pendant_output, "<Idle", 5) == 0);
    pendant_output[0] = '\0';
    engine_ticks = 2099;
    engine_execute_tasks(STATE_IDLE);
    CHECK(pendant_output[0] == '\0');
    engine_ticks = 2100;
    engine_execute_tasks(STATE_IDLE);
    CHECK(strncmp(pendant_output, "<Idle", 5) == 0);
    CHECK(primary_output[0] == '\0');
    return EXIT_SUCCESS;
}
