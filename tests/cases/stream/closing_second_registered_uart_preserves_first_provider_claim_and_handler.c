#include "support/stream_claim_host.h"
static io_stream_properties_t second_property;
static enqueue_realtime_command_ptr second_handler;
static unsigned second_releases, second_disables;
static bool second_disabled;
static enqueue_realtime_command_ptr second_set_handler(enqueue_realtime_command_ptr handler)
{
    enqueue_realtime_command_ptr previous = second_handler;
    second_handler = handler;
    return previous;
}
static bool second_disable(bool disable)
{
    second_disables++;
    second_disabled = disable;
    return true;
}
static const io_stream_t second_uart = {.type = StreamType_Serial, .instance = 2,
    .set_enqueue_rt_handler = second_set_handler, .disable_rx = second_disable};
static const io_stream_t *second_claim(uint32_t baud)
{
    CHECK(baud == 38400 && !second_property.flags.claimed);
    second_property.flags.claimed = true;
    return &second_uart;
}
static bool second_release(uint8_t instance)
{
    CHECK(instance == 2);
    second_releases++;
    second_property.flags.claimed = false;
    return true;
}
int main(void)
{
    prepare_stream_claim();
    second_property = (io_stream_properties_t){.type = StreamType_Serial, .instance = 2,
        .flags = {.claimable = true}, .claim = second_claim, .release = second_release};
    io_stream_details_t second_details = {.n_streams = 1, .streams = &second_property};
    stream_register_streams(&second_details);
    CHECK(stream_open_instance(1, 115200, auxiliary_handler, NULL) == &uart_device);
    CHECK(stream_open_instance(2, 38400, auxiliary_handler, NULL) == &second_uart);
    unsigned first_disables = disable_calls;
    CHECK(stream_close(&second_uart));
    CHECK(second_releases == 1 && second_disables == 1 && second_disabled);
    CHECK(!second_property.flags.claimed && uart_property.flags.claimed);
    CHECK(release_calls == 0 && disable_calls == first_disables && !receive_disabled);
    CHECK(uart_handler && uart_handler('?'));
    CHECK(stream_open_instance(2, 38400, auxiliary_handler, NULL) == &second_uart);
    CHECK(stream_close(&uart_device));
    CHECK(release_calls == 1 && !uart_property.flags.claimed);
    CHECK(second_property.flags.claimed && second_releases == 1);
    CHECK(second_handler && second_handler('?'));
    CHECK(stream_close(&second_uart));
    CHECK(second_releases == 2 && !second_property.flags.claimed);
    return EXIT_SUCCESS;
}
