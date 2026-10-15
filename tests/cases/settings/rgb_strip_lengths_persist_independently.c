#include "support/settings_host.h"
int main(void)
{
    prepare_settings_store();
    hal.rgb0.flags.is_strip = hal.rgb1.flags.is_strip = true;
    CHECK(store_setting(Setting_RGB_StripLengt0, "24") == Status_OK);
    CHECK(store_setting(Setting_RGB_StripLengt1, "60") == Status_OK);
    CHECK(settings.rgb_strip.length0 == 24 && settings.rgb_strip.length1 == 60);
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    CHECK(stored.rgb_strip.length0 == 24 && stored.rgb_strip.length1 == 60);
    CHECK(change_callbacks == 2);
    return EXIT_SUCCESS;
}
