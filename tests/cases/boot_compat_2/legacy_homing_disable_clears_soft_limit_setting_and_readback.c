#include "support/boot_legacy_limits_host.h"

static bool saw_enabled_soft_limits;
static void observe_before_disabling_homing(void)
{
    if(boot_reads == sizeof("$22=1\n$20=1\n") - 1)
        saw_enabled_soft_limits = settings.homing.flags.enabled &&
                                  settings.limits.soft_enabled.mask == AXES_BITMASK;
}
int main(void)
{
    legacy_read_observer = observe_before_disabling_homing;
    run_legacy_limit_board("$22=1\n$20=1\n$22=0\n$20\n$22\n");
    CHECK(saw_enabled_soft_limits);
    CHECK(!settings.homing.flags.enabled && !settings.limits.soft_enabled.mask);
    CHECK(!settings.limits.flags.jog_soft_limited);
    CHECK(strstr(engine_output, "$20=0" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "$22=0" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
