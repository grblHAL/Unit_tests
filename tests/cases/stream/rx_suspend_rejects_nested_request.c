#include "support/stream_suspend_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_suspend();
    CHECK(stream_rx_suspend(&receive_buffer, true));
    CHECK(!stream_rx_suspend(&receive_buffer, true));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Pending);
    CHECK(hal.stream.read() == SERIAL_NO_DATA);
    return EXIT_SUCCESS;
}
