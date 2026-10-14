#include "support/probe_settings_host.h"

int main(void)
{
    prepare_probe_settings();
    hal.driver_cap.toolsetter = hal.driver_cap.probe2 = true;
    CHECK(store_setting(Setting_ProbingFlags, "59") == Status_OK);
    const setting_detail_t *detail = setting_get_details(Setting_ProbingFlags, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 59);
    CHECK(probe_configure_calls == 1 && probe_select_calls == 0);
    CHECK(store_setting(Setting_ProbingFlags, "0") == Status_OK);
    CHECK(setting_get_int_value(detail, 0) == 0);
    CHECK(probe_configure_calls == 2 && probe_select_calls == 0);
    return EXIT_SUCCESS;
}
