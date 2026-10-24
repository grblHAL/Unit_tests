#include "homing_host.h"
int main(void)
{
    ha_start(true);
    settings.steppers.is_rotary.mask = bit(3);
    settings_changed_flags_t changed = {0};
    grbl.on_settings_changed(&settings, changed);
    CHECK(strcmp(grbl.on_set_axis_setting_unit((setting_id_t)(Setting_AxisExtended8 + 3), 3),
                 "deg/sec^2") == 0);
    CHECK(strcmp(grbl.on_set_axis_setting_unit(Setting_AxisExtended8, 0), "mm/sec^2") == 0);
    ha_set(3, 12);
    ha_rate(8);
    NEAR(acceleration[3], 12);
    ha_complete(8, true);
    NEAR(acceleration[3], 0);
    return 0;
}
