#include "support/stream_claim_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_claim();
    CHECK(stream_open_instance(1, 115200, auxiliary_handler, "Aux UART") == &uart_device);
    CHECK(claim_calls == 1 && requested_baud == 115200);
    CHECK(uart_property.flags.claimed);
    CHECK(uart_handler == auxiliary_handler && handler_calls == 1);
    CHECK(description_calls == 2 && strcmp(uart_description, "Aux UART") == 0);
    return EXIT_SUCCESS;
}
