#include "support/stream_claim_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_claim();
    CHECK(stream_open_instance(1, 19200, auxiliary_handler, NULL) == &uart_device);
    const io_stream_status_t *status = stream_get_uart_status(1);
    CHECK(status == &uart_status);
    CHECK(status->baud_rate == 19200 && status->flags.claimed);
    CHECK(stream_get_uart_status(9) == NULL);
    return EXIT_SUCCESS;
}
