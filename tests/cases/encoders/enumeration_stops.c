#include "hal.h"
#include "encoders.h"
#include "check.h"
static unsigned calls;
static bool visit(encoder_t *encoder, void *data) { *(encoder_t **)data = encoder; calls++; return true; }
int main(void)
{
    static encoder_t a = {0}, b = {0};
    encoder_register(&a); encoder_register(&b);
    encoder_t *seen = NULL; CHECK(encoders_enumerate(visit, &seen));
    CHECK(calls == 1); CHECK(seen == &a);
    return EXIT_SUCCESS;
}
