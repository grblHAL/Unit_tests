#include "support/stream_claim_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_claim();
    io_stream_details_t absent_provider = {0};
    stream_register_streams(&absent_provider);
    io_stream_flags_t flags = stream_get_flags(uart_device);
    CHECK(flags.claimable && flags.can_set_baud && !flags.claimed);
    CHECK(stream_open_instance(1, 115200, auxiliary_handler, NULL) == &uart_device);
    CHECK(stream_get_flags(uart_device).claimed);
    stream_register_streams(&absent_provider);
    CHECK(stream_get_flags(uart_device).claimed);
    CHECK(uart_handler && uart_handler('?'));
    CHECK(stream_close(&uart_device));
    flags = stream_get_flags(uart_device);
    CHECK(flags.claimable && flags.can_set_baud && !flags.claimed);
    CHECK(claim_calls == 1 && release_calls == 1);
    return EXIT_SUCCESS;
}
