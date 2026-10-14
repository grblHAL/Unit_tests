#include "support/probe_settings_host.h"

int main(void)
{
    prepare_probe_settings();
    hal.driver_cap.toolsetter = hal.driver_cap.probe2 = false;
    CHECK(store_setting(Setting_ProbingFlags, "59") == Status_OK);
    const setting_detail_t *detail = setting_get_details(Setting_ProbingFlags, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 35);
    CHECK(settings.probe.allow_feed_override && settings.probe.soft_limited);
    CHECK(settings.probe.enable_protection);
    CHECK(!settings.probe.toolsetter_auto_select && !settings.probe.probe2_auto_select);
    return EXIT_SUCCESS;
}
