#include "support/stream_claim_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_claim();
    CHECK(stream_open_instance(1, 115200, auxiliary_handler, NULL) == &uart_device);
    CHECK(stream_close(&uart_device));
    CHECK(receive_disabled && disable_calls == 1);
    CHECK(release_calls == 1 && !uart_property.flags.claimed);
    return EXIT_SUCCESS;
}
