#include "homing_host.h"
int main(void)
{
    ha_start(false);
    ha_rate(1);
    ha_complete(1, true);
    CHECK(rate_calls == 0 && complete_calls == 0);
    settings_changed_flags_t changed = {0};
    grbl.on_settings_changed(&settings, changed);
    CHECK(grbl.on_set_axis_setting_unit(Setting_SettingsMax, 0) == NULL);
    NEAR(acceleration[0], 0);
    return 0;
}
