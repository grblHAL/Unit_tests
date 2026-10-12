#include "support/stream_suspend_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_suspend();
    CHECK(!stream_rx_suspend(&receive_buffer, false));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off);
    CHECK(hal.stream.read() == 'G');
    return EXIT_SUCCESS;
}
