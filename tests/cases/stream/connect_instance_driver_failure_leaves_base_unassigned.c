#include "support/stream_claim_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_claim();
    claim_fails = true;
    CHECK(!stream_connect_instance(1, 115200));
    CHECK(claim_calls == 1);
    CHECK(stream_get_base() == NULL);
    CHECK(!uart_property.flags.claimed);
    return EXIT_SUCCESS;
}
