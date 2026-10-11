#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.coolant.on_delay = 1000;
    CHECK(store_setting(Setting_CoolantOnDelay, "1") == Status_SettingDisabled);
    CHECK(settings.coolant.on_delay == 1000);
    return EXIT_SUCCESS;
}
