#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    hal.motor_fault_cap.a.mask = 7;
    settings.motor_fault_enable.mask = 5;
    CHECK(store_setting(Setting_MotorFaultsEnable, "8") == Status_SettingValueOutOfRange);
    CHECK(settings.motor_fault_enable.mask == 5);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
