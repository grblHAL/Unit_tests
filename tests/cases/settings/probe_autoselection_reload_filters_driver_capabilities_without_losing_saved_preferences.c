#include "support/settings_initialized_host.h"
#include "support/probe_settings_host.h"
int main(void)
{
    prepare_initialized_settings(2.0f);
    hal.probe.get_state = settings_probe_state;
    hal.probe.configure = settings_probe_configure;
    hal.probe.select = settings_probe_select;
    hal.driver_cap.toolsetter = hal.driver_cap.probe2 = true;
    CHECK(store_setting(Setting_ProbingFlags, "24") == Status_OK);
    settings_init();
    CHECK(settings.probe.probe2_auto_select && settings.probe.toolsetter_auto_select);
    hal.driver_cap.probe2 = false;
    settings_init();
    CHECK(!settings.probe.probe2_auto_select && settings.probe.toolsetter_auto_select);
    settings_t saved;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL, sizeof(saved), true));
    CHECK(saved.probe.probe2_auto_select && saved.probe.toolsetter_auto_select);
    hal.driver_cap.probe2 = true;
    hal.driver_cap.toolsetter = false;
    settings_init();
    CHECK(settings.probe.probe2_auto_select && !settings.probe.toolsetter_auto_select);
    hal.driver_cap.probe2 = false;
    settings_init();
    CHECK(!settings.probe.probe2_auto_select && !settings.probe.toolsetter_auto_select);
    hal.driver_cap.probe2 = hal.driver_cap.toolsetter = true;
    hal.probe.select = NULL;
    settings_init();
    CHECK(!settings.probe.probe2_auto_select && !settings.probe.toolsetter_auto_select);
    hal.probe.select = settings_probe_select;
    settings_init();
    CHECK(settings.probe.probe2_auto_select && settings.probe.toolsetter_auto_select);
    CHECK(probe_select_calls == 0);
    const setting_detail_t *detail = setting_get_details(Setting_ProbingFlags, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 24);
    return EXIT_SUCCESS;
}
