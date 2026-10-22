#include "hal.h"
#include "encoders.h"
#include "support/malloc_failure_host.h"
#include "check.h"
static unsigned calls;
static bool visit(encoder_t *encoder, void *data)
{
    CHECK(calls < 3); ((encoder_t **)data)[calls++] = encoder; return false;
}
int main(void)
{
    // Driver registration can fail when the shared embedded heap is exhausted.
    static encoder_t first = {0}, second = {0}, third = {0};
    fail_malloc = true; encoder_register(&first); fail_malloc = false;
    CHECK(encoders_get_count() == 0 && failed_malloc_calls == 1);
    encoder_register(&first); CHECK(encoders_get_count() == 1);
    fail_malloc = true; encoder_register(&second); fail_malloc = false;
    CHECK(encoders_get_count() == 1 && failed_malloc_calls == 2);
    encoder_register(&second); CHECK(encoders_get_count() == 2);
    fail_malloc = true; encoder_register(&third); fail_malloc = false;
    CHECK(encoders_get_count() == 2 && failed_malloc_calls == 3);
    encoder_register(&third); CHECK(encoders_get_count() == 3);
    encoder_t *seen[3] = {0}; CHECK(!encoders_enumerate(visit, seen));
    CHECK(calls == 3 && seen[0] == &first && seen[1] == &second && seen[2] == &third);
    return EXIT_SUCCESS;
}
