#include "support/control_host.h"
#include "check.h"

int main(void)
{
    limit_signals_t signals = {.min.mask = 1, .max.mask = 2, .min2.mask = 4, .max2.mask = 1};
    CHECK(limit_signals_merge(signals).mask == 7);
    signals.bits = 0; CHECK(limit_signals_merge(signals).mask == 0);
    return EXIT_SUCCESS;
}
