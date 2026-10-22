#include "support/settings_host.h"
#include "check.h"
#include "config.h"

int main(void)
{
    prepare_settings_store();
    const setting_detail_t *detail = setting_get_details(Setting_InvertStepperEnable, NULL);
    CHECK(detail && detail->datatype == Format_Bool);
    CHECK(store_setting(Setting_InvertStepperEnable, "2") == Status_SettingValueOutOfRange);
    const setting_detail_t *limit = setting_get_details(Setting_LimitPinsInvertMask, NULL);
    CHECK(limit && limit->datatype == Format_Bool);
    CHECK(store_setting(Setting_InvertStepperEnable, "1") == Status_OK);
    CHECK(settings.steppers.enable_invert.mask == 0);
    CHECK(setting_get_int_value(detail, 0) == 1);
    CHECK(store_setting(Setting_LimitPinsInvertMask, "1") == Status_OK);
    CHECK(settings.limits.invert.mask == ((~DEFAULT_LIMIT_SIGNALS_INVERT_MASK) & AXES_BITMASK));
    CHECK(setting_get_int_value(limit, 0) == 1);
    CHECK(store_setting(Setting_InvertStepperEnable, "0") == Status_OK);
    CHECK(settings.steppers.enable_invert.mask == AXES_BITMASK);
    CHECK(setting_get_int_value(detail, 0) == 0);
    CHECK(store_setting(Setting_LimitPinsInvertMask, "0") == Status_OK);
    CHECK(settings.limits.invert.mask == DEFAULT_LIMIT_SIGNALS_INVERT_MASK);
    CHECK(setting_get_int_value(limit, 0) == 0);
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    CHECK(stored.steppers.enable_invert.mask == AXES_BITMASK);
    CHECK(stored.limits.invert.mask == DEFAULT_LIMIT_SIGNALS_INVERT_MASK);
    return EXIT_SUCCESS;
}
