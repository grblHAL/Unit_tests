#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.steppers.is_rotary.mask = 8;
    CHECK(store_setting(Settings_RotaryAxes, "32") == Status_SettingValueOutOfRange);
    CHECK(settings.steppers.is_rotary.mask == 8);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
