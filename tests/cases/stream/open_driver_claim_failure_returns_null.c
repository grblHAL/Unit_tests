#include "support/stream_claim_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_claim();
    claim_fails = true;
    CHECK(stream_open_instance(1, 115200, auxiliary_handler, "Aux") == NULL);
    CHECK(claim_calls == 1 && handler_calls == 0 && description_calls == 0);
    CHECK(!uart_property.flags.claimed);
    return EXIT_SUCCESS;
}
