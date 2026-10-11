#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    hal.motor_fault_cap.a.mask = 7;
    CHECK(store_setting(Setting_MotorFaultsEnable, "5") == Status_OK);
    CHECK(settings.motor_fault_enable.mask == 5);
    const setting_detail_t *detail = setting_get_details(Setting_MotorFaultsEnable, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 5);
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    CHECK(stored.motor_fault_enable.mask == 5);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
