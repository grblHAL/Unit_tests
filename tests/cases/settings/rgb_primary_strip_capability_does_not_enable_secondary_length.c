#include "support/settings_host.h"
int main(void)
{
    prepare_settings_store();
    hal.rgb0.flags.is_strip = true;
    settings.rgb_strip.length1 = 60;
    CHECK(store_setting(Setting_RGB_StripLengt0, "24") == Status_OK);
    CHECK(store_setting(Setting_RGB_StripLengt1, "12") == Status_SettingDisabled);
    CHECK(settings.rgb_strip.length1 == 60 && change_callbacks == 1);
    return EXIT_SUCCESS;
}
