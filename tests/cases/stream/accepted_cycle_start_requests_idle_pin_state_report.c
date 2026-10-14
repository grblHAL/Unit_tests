#include "support/stream_rt_report_host.h"
int main(void)
{
    prepare_rt_reporting();
    CHECK(stream_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(rt_input_calls == 1 && rt_input_byte == CMD_CYCLE_START);
    CHECK(hal.stream.report.flags.cycle_start && rt_report_calls == 1);
    return EXIT_SUCCESS;
}
