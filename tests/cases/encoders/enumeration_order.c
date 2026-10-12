#include "hal.h"
#include "encoders.h"
#include "check.h"
static unsigned calls;
static bool visit(encoder_t *encoder, void *data) { ((encoder_t **)data)[calls++] = encoder; return false; }
int main(void)
{
    static encoder_t a = {0}, b = {0};
    encoder_register(&a); encoder_register(&b); CHECK(encoders_get_count() == 2);
    encoder_t *seen[2] = {0}; CHECK(!encoders_enumerate(visit, seen));
    CHECK(calls == 2); CHECK(seen[0] == &a); CHECK(seen[1] == &b);
    return EXIT_SUCCESS;
}
