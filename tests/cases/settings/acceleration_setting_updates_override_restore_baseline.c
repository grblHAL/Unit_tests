#include "support/settings_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    state_set(STATE_IDLE);
    CHECK(settings_override_acceleration(X_AXIS, 25));
    CHECK(store_setting(Setting_AxisAcceleration, "125") == Status_OK);
    CHECK(settings_override_acceleration(X_AXIS, 250));
    CHECK(settings_override_acceleration(X_AXIS, 0));
    NEAR(settings.axis[X_AXIS].acceleration, 450000);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
