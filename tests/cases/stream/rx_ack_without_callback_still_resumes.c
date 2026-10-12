#include "support/stream_suspend_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_suspend();
    grbl.on_toolchange_ack = NULL;
    CHECK(stream_rx_suspend(&receive_buffer, true));
    CHECK(receive_handler(CMD_TOOL_ACK));
    CHECK(receive_buffer.backup && acknowledged_calls == 0);
    CHECK(hal.stream.read == receive_read);
    CHECK(stream_rx_suspend(&receive_buffer, false));
    return EXIT_SUCCESS;
}
