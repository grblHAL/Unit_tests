#include "support/settings_host.h"
int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_StepInvertMask, "5") == Status_OK);
    CHECK(settings.steppers.step_invert.mask == 5);
    const setting_detail_t *detail = setting_get_details(Setting_StepInvertMask, NULL);
    CHECK(detail && setting_get_int_value(detail, 0) == 5);
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    CHECK(stored.steppers.step_invert.mask == 5 && change_callbacks == 1);
    return EXIT_SUCCESS;
}
