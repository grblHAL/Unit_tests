#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_AxisAcceleration + Y_AXIS, "2.5") == Status_OK);
    NEAR(settings.axis[Y_AXIS].acceleration, 9000);
    NEAR(settings.axis[X_AXIS].acceleration, 100);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
