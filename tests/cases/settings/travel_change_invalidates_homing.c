#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    sys.homed.bits = 7;
    CHECK(store_setting(Setting_AxisMaxTravel + Y_AXIS, "250") == Status_OK);
    NEAR(settings.axis[Y_AXIS].max_travel, -250);
    NEAR(settings.axis[X_AXIS].max_travel, -200);
    CHECK(sys.flags.travel_changed);
    CHECK(sys.homed.bits == 5);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
