#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_AxisMaxRate + Y_AXIS, "750") == Status_OK);
    NEAR(settings.axis[Y_AXIS].max_rate, 750);
    NEAR(settings.axis[X_AXIS].max_rate, 1000);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
