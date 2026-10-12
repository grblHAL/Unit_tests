#include "support/stream_claim_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_claim();
    uart_property.flags.claimable = false;
    CHECK(stream_open_instance(1, 115200, auxiliary_handler, NULL) == NULL);
    CHECK(claim_calls == 0);
    return EXIT_SUCCESS;
}
