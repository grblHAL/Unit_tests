#include "homing_host.h"
int main(void)
{
    ha_start(true);
    settings_changed_flags_t changed = {0};
    grbl.on_settings_changed(&settings, changed);
    CHECK(settings_calls == 1);
    CHECK(strcmp(grbl.on_set_axis_setting_unit(Setting_AxisExtended8, 0), "mm/sec^2") == 0);
    CHECK(strcmp(grbl.on_set_axis_setting_unit(Setting_SettingsMax, 0), "previous") == 0);
    grbl.on_settings_changed(&settings, changed);
    CHECK(settings_calls == 2);
    CHECK(strcmp(grbl.on_set_axis_setting_unit(Setting_AxisExtended8, 0), "mm/sec^2") == 0);
    return 0;
}
