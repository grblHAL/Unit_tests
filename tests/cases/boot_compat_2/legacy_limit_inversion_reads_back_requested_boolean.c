#include "support/boot_legacy_limits_host.h"

int main(void)
{
    run_legacy_limit_board("$5=1\n$5\n");
    CHECK(settings.limits.invert.mask == ((~DEFAULT_LIMIT_SIGNALS_INVERT_MASK) & AXES_BITMASK));
    CHECK(strstr(engine_output, "$5=1" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
