#include "support/stream_claim_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_claim();
    stream_set_defaults(&uart_device, 9600);
    CHECK(uart_handler == protocol_enqueue_realtime_command);
    CHECK(baud_calls == 1 && requested_baud == 9600);
    CHECK(format_calls == 1 && requested_format.value == 0);
    CHECK(disable_calls == 1 && !receive_disabled);
    CHECK(read_reset_calls == 1 && write_reset_calls == 1);
    return EXIT_SUCCESS;
}
