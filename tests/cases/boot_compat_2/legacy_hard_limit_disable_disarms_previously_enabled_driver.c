#include "support/boot_legacy_limits_host.h"

int main(void)
{
    run_legacy_limit_board("$21=1\n$21=0\n$21\n");
    CHECK(legacy_limits_saw_enable && !legacy_limits_enabled);
    CHECK(!settings.limits.flags.hard_enabled && !settings.limits.flags.check_at_init);
    CHECK(strstr(engine_output, "$21=0" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
