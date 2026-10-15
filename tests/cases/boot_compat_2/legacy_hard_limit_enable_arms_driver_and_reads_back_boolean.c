#include "support/boot_legacy_limits_host.h"

int main(void)
{
    run_legacy_limit_board("$21=1\n$21\n");
    CHECK(settings.limits.flags.hard_enabled);
    CHECK(legacy_limits_enable_calls > 0 && legacy_limits_enabled);
    CHECK(strstr(engine_output, "$21=1" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
