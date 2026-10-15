#include "support/mpg_stream_host.h"
int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    primary_output[0] = pendant_output[0] = '\0';
    settings.status_report.pin_state = true;
    CHECK(stream_mpg_check_enable(CMD_CYCLE_START));
    CHECK(sys.rt_exec_state & EXEC_CYCLE_START);
    CHECK(hal.stream.report.flags.cycle_start);
    CHECK(pendant_output[0] == '\0' && primary_output[0] == '\0');
    return EXIT_SUCCESS;
}
