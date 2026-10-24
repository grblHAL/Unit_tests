#include "support/settings_initialized_host.h"

static axes_signals_t ganged_y(bool auto_squared)
{
    return (axes_signals_t){.mask = auto_squared ? 0 : Y_AXIS_BIT};
}

int main(void)
{
    prepare_initialized_settings(2);
    hal.stepper.get_ganged = ganged_y;
    float percent = settings.homing.dual_axis.fail_length_percent;
    float minimum = settings.homing.dual_axis.fail_distance_min;
    float maximum = settings.homing.dual_axis.fail_distance_max;
    const setting_id_t ids[] = {Setting_DualAxisLengthFailPercent, Setting_DualAxisLengthFailMin, Setting_DualAxisLengthFailMax};
    for(unsigned i = 0; i < 3; i++) {
        CHECK(setting_get_details(ids[i], NULL) == NULL);
        CHECK(store_setting(ids[i], "3") == Status_SettingDisabled);
    }
    CHECK(hal.stepper.get_ganged(false).y && hal.stepper.get_ganged(true).mask == 0);
    NEAR(settings.homing.dual_axis.fail_length_percent, percent);
    NEAR(settings.homing.dual_axis.fail_distance_min, minimum);
    NEAR(settings.homing.dual_axis.fail_distance_max, maximum);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
