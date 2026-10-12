#include "hal.h"
#include "encoders.h"
#include "check.h"
static unsigned calls;
static bool visit(encoder_t *encoder, void *data) { (void)encoder; (void)data; calls++; return false; }
int main(void)
{
    CHECK(encoders_get_count() == 0);
    CHECK(!encoders_enumerate(visit, NULL)); CHECK(calls == 0);
    return EXIT_SUCCESS;
}
