#include "support/energized_motor_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_energized_motor_settings();
    CHECK(store_setting(Setting_SteppersEnergize, "5") == Status_OK);
    const char *invalid[] = {"enabled", "-1", "1.5", "4294967296"};
    for(unsigned i = 0; i < sizeof(invalid) / sizeof(invalid[0]); i++) {
        CHECK(store_setting(Setting_SteppersEnergize, invalid[i]) == Status_BadNumberFormat);
        CHECK(settings.steppers.energize.mask == 5 && requested_motor_mask.mask == 5);
        CHECK(motor_enable_calls == 1 && change_callbacks == 1);
        settings_t stored;
        CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
        CHECK(stored.steppers.energize.mask == 5);
    }
    CHECK(store_setting(Setting_SteppersEnergize, "3") == Status_OK);
    CHECK(settings.steppers.energize.mask == 3 && requested_motor_mask.mask == 3);
    CHECK(motor_enable_calls == 2 && change_callbacks == 2);
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    CHECK(stored.steppers.energize.mask == 3);
    return EXIT_SUCCESS;
}
