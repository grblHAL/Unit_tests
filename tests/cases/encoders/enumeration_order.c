#include "hal.h"
#include "encoders.h"
#include "check.h"
static unsigned calls;
static bool visit(encoder_t *encoder, void *data) { CHECK(calls < 3); ((encoder_t **)data)[calls++] = encoder; return false; }
int main(void)
{
    static encoder_t a = {0}, b = {0}, c = {0};
    encoder_register(&a); encoder_register(&b); encoder_register(&c);
    CHECK(encoders_get_count() == 3);
    encoder_t *seen[3] = {0}; CHECK(!encoders_enumerate(visit, seen));
    CHECK(calls == 3); CHECK(seen[0] == &a); CHECK(seen[1] == &b); CHECK(seen[2] == &c);
    return EXIT_SUCCESS;
}
