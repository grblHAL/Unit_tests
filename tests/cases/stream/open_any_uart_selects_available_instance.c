#include "support/stream_claim_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_claim();
    CHECK(stream_open_instance(255, 9600, auxiliary_handler, NULL) == &uart_device);
    CHECK(claim_calls == 1 && requested_baud == 9600);
    CHECK(description_calls == 0);
    return EXIT_SUCCESS;
}
