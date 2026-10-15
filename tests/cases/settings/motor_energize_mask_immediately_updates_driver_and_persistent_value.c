#include "support/energized_motor_settings_host.h"
int main(void)
{
    prepare_energized_motor_settings();
    CHECK(store_setting(Setting_SteppersEnergize, "5") == Status_OK);
    CHECK(settings.steppers.energize.mask == 5 && requested_motor_mask.mask == 5);
    CHECK(motor_enable_calls == 1 && change_callbacks == 1);
    const setting_detail_t *detail = setting_get_details(Setting_SteppersEnergize, NULL);
    CHECK(detail && setting_get_int_value(detail, 0) == 5);
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    CHECK(stored.steppers.energize.mask == 5);
    return EXIT_SUCCESS;
}
