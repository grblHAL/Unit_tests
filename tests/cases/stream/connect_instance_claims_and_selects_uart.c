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
    return EXIT_SUCCESS;
}
