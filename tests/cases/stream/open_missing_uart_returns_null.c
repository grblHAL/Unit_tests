#include "support/stream_claim_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_claim();
    CHECK(stream_open_instance(9, 115200, auxiliary_handler, NULL) == NULL);
    CHECK(claim_calls == 0 && handler_calls == 0);
    return EXIT_SUCCESS;
}
