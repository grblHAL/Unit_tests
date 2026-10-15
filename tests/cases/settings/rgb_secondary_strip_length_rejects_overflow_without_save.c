#include "support/settings_host.h"
int main(void)
{
    prepare_settings_store();
    hal.rgb1.flags.is_strip = true;
    CHECK(store_setting(Setting_RGB_StripLengt1, "42") == Status_OK);
    change_callbacks = 0;
    CHECK(store_setting(Setting_RGB_StripLengt1, "256") == Status_SettingValueOutOfRange);
    CHECK(settings.rgb_strip.length1 == 42 && change_callbacks == 0);
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    CHECK(stored.rgb_strip.length1 == 42);
    return EXIT_SUCCESS;
}
