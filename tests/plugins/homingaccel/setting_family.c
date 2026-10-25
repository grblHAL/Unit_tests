#include "homing_host.h"
int main(void)
{
    ha_start(true);
    const setting_detail_t *s = registered_settings->settings;
    CHECK(((setting_set_float_ptr)s->value)(Setting_SettingsMax, 4) == Status_SettingDisabled);
    NEAR(((setting_get_float_ptr)s->get_value)(Setting_SettingsMax), 0);
    NEAR(ha_get(0), 10);
    return 0;
}
