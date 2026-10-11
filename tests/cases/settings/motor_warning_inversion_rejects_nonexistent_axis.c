#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    hal.motor_warning_cap.a.mask = 7;
    settings.motor_warning_invert.mask = 5;
    CHECK(store_setting(Setting_MotorWarningsInvert, "8") == Status_SettingValueOutOfRange);
    CHECK(settings.motor_warning_invert.mask == 5);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
