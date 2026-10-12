#include "support/stream_claim_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_claim();
    io_stream_flags_t flags = stream_get_flags(uart_device);
    CHECK(flags.claimable && flags.can_set_baud && !flags.claimed);
    CHECK(stream_open_instance(1, 115200, auxiliary_handler, NULL) == &uart_device);
    CHECK(stream_get_flags(uart_device).claimed);
    return EXIT_SUCCESS;
}
