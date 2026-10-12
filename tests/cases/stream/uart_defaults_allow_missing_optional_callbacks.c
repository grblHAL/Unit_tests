#include "support/stream_claim_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_claim();
    io_stream_t minimal = uart_device;
    minimal.set_baud_rate = NULL;
    minimal.set_format = NULL;
    minimal.disable_rx = NULL;
    minimal.reset_write_buffer = NULL;
    stream_set_defaults(&minimal, 9600);
    CHECK(uart_handler == protocol_enqueue_realtime_command);
    CHECK(read_reset_calls == 1);
    CHECK(baud_calls == 0 && format_calls == 0 && disable_calls == 0 && write_reset_calls == 0);
    return EXIT_SUCCESS;
}
