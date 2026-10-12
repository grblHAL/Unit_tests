#include "support/primary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_primary_pwm_settings(true);
    CHECK(store_setting(Setting_SpindleOnDelay, "1.25") == Status_OK);
    CHECK(settings.spindle.on_delay == 1250);
    NEAR(setting_get_float_value(setting_get_details(Setting_SpindleOnDelay, NULL), 0), 1.25f);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
