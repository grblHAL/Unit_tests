#include "support/settings_host.h"
int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_InvertStepperEnable, "5") == Status_OK);
    CHECK(settings.steppers.enable_invert.mask == 5);
    const setting_detail_t *detail = setting_get_details(Setting_InvertStepperEnable, NULL);
    CHECK(detail && setting_get_int_value(detail, 0) == 5);
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    CHECK(stored.steppers.enable_invert.mask == 5 && change_callbacks == 1);
    return EXIT_SUCCESS;
}
