#include "support/stream_rt_report_host.h"
int main(void)
{
    prepare_rt_reporting();
    settings.status_report.pin_state = false;
    CHECK(stream_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(!hal.stream.report.flags.cycle_start && rt_report_calls == 0);
    return EXIT_SUCCESS;
}
