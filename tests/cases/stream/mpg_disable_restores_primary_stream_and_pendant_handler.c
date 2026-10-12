#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    CHECK(stream_mpg_enable(true));
    CHECK(stream_mpg_enable(false));
    CHECK(!sys.mpg_mode && !hal.stream.state.is_mpg);
    CHECK(!primary_rx_disabled);
    CHECK(hal.stream.read == primary_input);
    CHECK(hal.stream.write == primary_write);
    CHECK(primary_rt == protocol_enqueue_realtime_command);
    CHECK(pendant_rt == stream_mpg_check_enable);
    CHECK(primary_resets == 1 && pendant_resets == 1);
    return EXIT_SUCCESS;
}
