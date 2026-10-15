#include "support/settings_initialized_host.h"
int main(void)
{
    prepare_initialized_settings(2);
    CHECK(store_setting(Setting_AxisMaxTravel + 7, "450") == Status_OK);
    sys.homed.mask = 255;
    sys.flags.travel_changed = false;
    CHECK(store_setting(Setting_AxisMaxTravel + 7, "450") == Status_OK);
    CHECK(sys.homed.mask == 255 && !sys.flags.travel_changed);
    NEAR(settings.axis[7].max_travel, -450);
    return EXIT_SUCCESS;
}
