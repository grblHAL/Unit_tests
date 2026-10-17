#include "support/mpg_stream_host.h"
int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    CHECK(stream_mpg_enable(true));
    CHECK(protocol_enqueue_realtime_command(CMD_MPG_MODE_TOGGLE));
    CHECK(sys.mpg_mode && hal.stream.read == pendant_input);
    engine_execute_tasks(STATE_IDLE);
    CHECK(!sys.mpg_mode && !hal.stream.state.is_mpg);
    CHECK(hal.stream.read == primary_input && !primary_rx_disabled);
    CHECK(hal.stream.write == primary_write && pendant_rt == stream_mpg_check_enable);
    return EXIT_SUCCESS;
}
