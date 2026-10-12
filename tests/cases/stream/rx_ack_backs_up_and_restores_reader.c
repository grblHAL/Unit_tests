#include "support/stream_suspend_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_suspend();
    CHECK(stream_rx_suspend(&receive_buffer, true));
    CHECK(receive_handler(CMD_TOOL_ACK));
    CHECK(acknowledged_calls == 1);
    CHECK(receive_buffer.backup);
    CHECK(receive_buffer.tail == receive_buffer.head);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Active);
    CHECK(hal.stream.read == receive_read);
    CHECK(receive_handler == receive_realtime);
    return EXIT_SUCCESS;
}
