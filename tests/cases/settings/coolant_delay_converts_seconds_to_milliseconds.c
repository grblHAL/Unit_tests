#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    hal.coolant_cap.flood = true;
    CHECK(store_setting(Setting_CoolantOnDelay, "1.25") == Status_OK);
    CHECK(settings.coolant.on_delay == 1250);
    NEAR(setting_get_float_value(setting_get_details(Setting_CoolantOnDelay, NULL), 0), 1.25f);
    return EXIT_SUCCESS;
}
