#include "support/settings_host.h"
int main(void)
{
    prepare_settings_store();
    hal.rgb0.flags.is_strip = true;
    settings.rgb_strip.length0 = 24;
    CHECK(store_setting(Setting_RGB_StripLengt0, "abc") == Status_BadNumberFormat);
    CHECK(settings.rgb_strip.length0 == 24 && change_callbacks == 0);
    return EXIT_SUCCESS;
}
