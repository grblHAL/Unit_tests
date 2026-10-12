#include "support/stream_suspend_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_suspend();
    CHECK(stream_rx_suspend(&receive_buffer, true));
    CHECK(!receive_handler('X'));
    CHECK(forwarded_calls == 1 && last_forwarded_byte == 'X');
    CHECK(acknowledged_calls == 0);
    return EXIT_SUCCESS;
}
