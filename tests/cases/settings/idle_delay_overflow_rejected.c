#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.steppers.idle_lock_time = 250;
    CHECK(store_setting(Setting_StepperIdleLockTime, "65536") == Status_SettingValueOutOfRange);
    CHECK(settings.steppers.idle_lock_time == 250);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
