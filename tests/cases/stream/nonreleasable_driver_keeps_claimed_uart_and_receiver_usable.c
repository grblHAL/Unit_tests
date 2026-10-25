#include "support/stream_claim_host.h"
int main(void)
{
    engine_prepare();
    uart_property = (io_stream_properties_t){.type = StreamType_Serial, .instance = 1,
        .flags = {.claimable = true, .can_set_baud = true}, .claim = uart_claim,
        .get_status = uart_get_status};
    io_stream_details_t details = {.n_streams = 1, .streams = &uart_property};
    stream_register_streams(&details);
    CHECK(stream_open_instance(1, 115200, auxiliary_handler, NULL) == &uart_device);
    CHECK(uart_property.flags.claimed && claim_calls == 1);
    unsigned disables_before = disable_calls;
    CHECK(!stream_close(&uart_device));
    CHECK(disable_calls == disables_before && !receive_disabled);
    CHECK(release_calls == 0 && uart_property.flags.claimed);
    CHECK(uart_handler != NULL && uart_handler('?'));
    CHECK(!uart_handler('x'));
    CHECK(stream_open_instance(1, 115200, auxiliary_handler, NULL) == NULL);
    CHECK(claim_calls == 1 && uart_property.flags.claimed);
    CHECK(!stream_close(&uart_device));
    CHECK(release_calls == 0 && disable_calls == disables_before);
    return EXIT_SUCCESS;
}
