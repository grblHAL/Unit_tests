#include "support/mpg_stream_host.h"
int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    /* Unused top-bit realtime bytes are consumed, not parsed as G-code. */
    CHECK(protocol_enqueue_realtime_command(CMD_MPG_MODE_TOGGLE));
    engine_execute_tasks(STATE_IDLE);
    CHECK(!sys.mpg_mode && hal.stream.read == primary_input);
    CHECK(!primary_rx_disabled && pendant_rx_disabled);
    return EXIT_SUCCESS;
}
