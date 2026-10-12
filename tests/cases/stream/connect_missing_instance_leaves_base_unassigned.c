#include "support/stream_claim_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_claim();
    CHECK(!stream_connect_instance(2, 115200));
    CHECK(claim_calls == 0);
    CHECK(stream_get_base() == NULL);
    return EXIT_SUCCESS;
}
