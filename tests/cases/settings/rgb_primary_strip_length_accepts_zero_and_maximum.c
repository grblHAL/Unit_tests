#include "support/settings_host.h"
int main(void)
{
    prepare_settings_store();
    hal.rgb0.flags.is_strip = true;
    CHECK(store_setting(Setting_RGB_StripLengt0, "255") == Status_OK);
    CHECK(settings.rgb_strip.length0 == 255);
    CHECK(store_setting(Setting_RGB_StripLengt0, "0") == Status_OK);
    CHECK(settings.rgb_strip.length0 == 0);
    CHECK(change_callbacks == 2);
    return EXIT_SUCCESS;
}
