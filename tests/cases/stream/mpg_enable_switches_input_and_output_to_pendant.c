#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    CHECK(stream_mpg_enable(true));
    CHECK(sys.mpg_mode && hal.stream.state.is_mpg);
    CHECK(primary_rx_disabled && !pendant_rx_disabled);
    CHECK(hal.stream.read == pendant_input);
    CHECK(hal.stream.write == write_pendant);
    CHECK(pendant_rt == protocol_enqueue_realtime_command);
    CHECK(pendant_resets == 1);
    CHECK(primary_resets == 0);
    return EXIT_SUCCESS;
}
