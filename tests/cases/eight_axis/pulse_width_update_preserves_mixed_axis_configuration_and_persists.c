#include "support/rotary_limit_settings_host.h"

int main(void)
{
    prepare_rotary_limit_settings();
    CHECK(system_n_axis() == 8);
    CHECK(store_setting(Setting_PulseMicroseconds, "8.5") == Status_OK);
    NEAR(settings.steppers.pulse_microseconds, 8.5f);
    CHECK(settings.steppers.is_rotary.mask == 40);
    CHECK(change_callbacks == 1);
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    NEAR(stored.steppers.pulse_microseconds, 8.5f);
    CHECK(stored.steppers.is_rotary.mask == 40);
    return EXIT_SUCCESS;
}
