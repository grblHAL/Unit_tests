#include "support/settings_initialized_host.h"

static axes_signals_t squared_y(bool auto_squared)
{
    (void)auto_squared;
    return (axes_signals_t){.y = true};
}

int main(void)
{
    prepare_initialized_settings(2);
    hal.stepper.get_ganged = squared_y;
    const setting_id_t ids[] = {Setting_DualAxisLengthFailPercent, Setting_DualAxisLengthFailMin, Setting_DualAxisLengthFailMax};
    const char *values[] = {"3.5", "0.5", "8"};
    const float expected[] = {3.5f, 0.5f, 8.0f};
    for(unsigned i = 0; i < 3; i++) {
        const setting_detail_t *detail = setting_get_details(ids[i], NULL);
        CHECK(detail != NULL);
        CHECK(store_setting(ids[i], values[i]) == Status_OK);
        NEAR(setting_get_float_value(detail, 0), expected[i]);
    }
    CHECK(change_callbacks == 3);
    settings_init();
    NEAR(settings.homing.dual_axis.fail_length_percent, 3.5f);
    NEAR(settings.homing.dual_axis.fail_distance_min, 0.5f);
    NEAR(settings.homing.dual_axis.fail_distance_max, 8);
    CHECK(hal.stepper.get_ganged(true).y);
    return EXIT_SUCCESS;
}
