#include "support/stream_suspend_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_suspend();
    CHECK(stream_rx_suspend(&receive_buffer, true));
    CHECK(receive_handler(CMD_TOOL_ACK));
    memset(receive_buffer.data, 'Z', 5);
    receive_buffer.head = receive_buffer.tail = 10;
    CHECK(stream_rx_suspend(&receive_buffer, false));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off);
    CHECK(!receive_buffer.backup);
    CHECK(receive_buffer.head == 5 && receive_buffer.tail == 0);
    CHECK(memcmp(receive_buffer.data, "G0X1\n", 5) == 0);
    CHECK(hal.stream.read() == 'G');
    return EXIT_SUCCESS;
}
