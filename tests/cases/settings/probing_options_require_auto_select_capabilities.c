#include "support/probe_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_settings();
    CHECK(store_setting(Setting_ProbingFlags, "59") == Status_OK);
    CHECK(settings.probe.allow_feed_override);
    CHECK(settings.probe.soft_limited);
    CHECK(settings.probe.enable_protection);
    CHECK(!settings.probe.toolsetter_auto_select);
    CHECK(!settings.probe.probe2_auto_select);
    CHECK(probe_configure_calls == 1);
    CHECK(probe_select_calls == 0);
    return EXIT_SUCCESS;
}
