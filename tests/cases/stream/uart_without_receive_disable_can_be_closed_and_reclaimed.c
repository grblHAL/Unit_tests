#include "support/stream_claim_host.h"
static io_stream_t optional_uart;
static const io_stream_t *claim_optional_uart(uint32_t baud)
{
    return uart_claim(baud) ? &optional_uart : NULL;
}

int main(void)
{
    engine_prepare();
    optional_uart = uart_device;
    optional_uart.disable_rx = NULL;
    uart_property = (io_stream_properties_t){.type = StreamType_Serial, .instance = 1,
        .flags = {.claimable = true, .can_set_baud = true}, .claim = claim_optional_uart,
        .release = uart_release, .get_status = uart_get_status};
    static io_stream_details_t details = {.n_streams = 1, .streams = &uart_property};
    stream_register_streams(&details);
    const uint32_t rates[] = {115200, 9600};
    for(unsigned attempt = 0; attempt < 2; attempt++) {
        CHECK(stream_open_instance(1, rates[attempt], auxiliary_handler, NULL) == &optional_uart);
        CHECK(uart_property.flags.claimed && requested_baud == rates[attempt]);
        CHECK(uart_handler && uart_handler('?') && !uart_handler('x'));
        CHECK(stream_close(&optional_uart));
        CHECK(!uart_property.flags.claimed && release_calls == attempt + 1);
        CHECK(disable_calls == 0);
    }
    CHECK(claim_calls == 2);
    return EXIT_SUCCESS;
}
