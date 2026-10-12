#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    settings.mpg_report_interval = 0;
    engine_ticks = 2000;
    engine_execute_tasks(STATE_IDLE);
    CHECK(pendant_output[0] == '\0');
    return EXIT_SUCCESS;
}
