#include "support/settings_initialized_host.h"
int main(void)
{
    prepare_initialized_settings(2);
    CHECK(N_AXIS == 8);
    sys.homed.mask = 255;
    sys.flags.travel_changed = false;
    CHECK(store_setting(Setting_AxisMaxTravel + 7, "450") == Status_OK);
    CHECK(sys.homed.mask == 127 && sys.flags.travel_changed);
    NEAR(settings.axis[7].max_travel, -450);
    settings.axis[7].max_travel = -1;
    settings_init();
    NEAR(settings.axis[7].max_travel, -450);
    const setting_detail_t *detail = setting_get_details(Setting_AxisMaxTravel + 7, NULL);
    CHECK(detail != NULL);
    NEAR(setting_get_float_value(detail, 7), 450);
    return EXIT_SUCCESS;
}
