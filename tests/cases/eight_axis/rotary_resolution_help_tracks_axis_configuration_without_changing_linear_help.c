#include "support/settings_initialized_host.h"

int main(void)
{
    prepare_initialized_settings(2);
    CHECK(store_setting(Settings_RotaryAxes, "1") == Status_OK);
    const char *rotary = setting_get_description((setting_id_t)(Setting_AxisStepsPerMM + A_AXIS));
    CHECK(rotary && strstr(rotary, "steps per degree"));
    const char *linear = setting_get_description(Setting_AxisStepsPerMM);
    CHECK(linear && strstr(linear, "steps per millimeter"));
    CHECK(store_setting(Settings_RotaryAxes, "0") == Status_OK);
    linear = setting_get_description((setting_id_t)(Setting_AxisStepsPerMM + A_AXIS));
    CHECK(linear && strstr(linear, "steps per millimeter"));
    return EXIT_SUCCESS;
}
