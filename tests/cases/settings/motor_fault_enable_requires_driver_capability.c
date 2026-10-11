#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    hal.motor_fault_cap.a.mask = 0;
    settings.motor_fault_enable.mask = 5;
    CHECK(store_setting(Setting_MotorFaultsEnable, "3") == Status_SettingDisabled);
    CHECK(settings.motor_fault_enable.mask == 5);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
