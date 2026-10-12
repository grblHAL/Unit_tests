#include "support/stream_suspend_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_suspend();
    CHECK(stream_rx_suspend(&receive_buffer, true));
    CHECK(stream_rx_suspend(&receive_buffer, false));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off);
    CHECK(hal.stream.read == receive_read);
    CHECK(receive_handler == receive_realtime);
    CHECK(receive_buffer.head == 5 && receive_buffer.tail == 0);
    CHECK(acknowledged_calls == 0);
    return EXIT_SUCCESS;
}
