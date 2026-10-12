#include "support/probe_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_settings();
    hal.driver_cap.toolsetter = hal.driver_cap.probe2 = true;
    CHECK(store_setting(Setting_ProbingFlags, "24") == Status_OK);
    CHECK(settings.probe.toolsetter_auto_select);
    CHECK(settings.probe.probe2_auto_select);
    CHECK(!settings.probe.allow_feed_override);
    CHECK(!settings.probe.soft_limited);
    CHECK(probe_configure_calls == 1);
    CHECK(probe_select_calls == 0);
    return EXIT_SUCCESS;
}
