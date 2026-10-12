#include "support/stream_suspend_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_suspend();
    CHECK(stream_rx_suspend(&receive_buffer, true));
    CHECK(receive_handler(CMD_STATUS_REPORT));
    CHECK(forwarded_calls == 1 && last_forwarded_byte == CMD_STATUS_REPORT);
    CHECK(acknowledged_calls == 0);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Pending);
    return EXIT_SUCCESS;
}
