#include "hal.h"
#include "encoders.h"
#include "support/malloc_failure_host.h"
#include "check.h"
static unsigned calls;
static bool visit(encoder_t *encoder, void *data)
{
    CHECK(calls < 2); ((encoder_t **)data)[calls++] = encoder; return false;
}
int main(void)
{
    // Driver registration can fail when the shared embedded heap is exhausted.
    static encoder_t first = {0}, second = {0};
    fail_malloc = true; encoder_register(&first); fail_malloc = false;
    CHECK(encoders_get_count() == 0 && failed_malloc_calls == 1);
    encoder_register(&first); CHECK(encoders_get_count() == 1);
    fail_malloc = true; encoder_register(&second); fail_malloc = false;
    CHECK(encoders_get_count() == 1 && failed_malloc_calls == 2);
    encoder_register(&second); CHECK(encoders_get_count() == 2);
    encoder_t *seen[2] = {0}; CHECK(!encoders_enumerate(visit, seen));
    CHECK(calls == 2 && seen[0] == &first && seen[1] == &second);
    return EXIT_SUCCESS;
}
