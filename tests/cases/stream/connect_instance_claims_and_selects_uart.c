#include "support/stream_claim_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_claim();
    CHECK(stream_connect_instance(1, 115200));
    CHECK(claim_calls == 1);
    CHECK(requested_baud == 115200);
    CHECK(stream_get_base() == &uart_device);
    CHECK(hal.stream.instance == 1);
    CHECK(uart_handler == protocol_enqueue_realtime_command);
    CHECK(description_calls == 2);
    CHECK(strcmp(uart_description, "Primary UART") == 0);
    unsigned disables_before = disable_calls;
    enqueue_realtime_command_ptr handler_before = uart_handler;
    CHECK(!stream_close(stream_get_base()));
    CHECK(release_calls == 0 && disable_calls == disables_before);
    CHECK(uart_property.flags.claimed && stream_get_base() == &uart_device);
    CHECK(uart_handler == handler_before && hal.stream.instance == 1);
    CHECK(stream_open_instance(1, 38400, auxiliary_handler, NULL) == NULL);
    CHECK(claim_calls == 1 && requested_baud == 115200);
    return EXIT_SUCCESS;
}
