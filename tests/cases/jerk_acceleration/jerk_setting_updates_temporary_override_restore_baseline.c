#include "support/settings_host.h"
#include "state_machine.h"
#include "nvs.h"
int main(void)
{
    prepare_settings_store();
    state_set(STATE_IDLE);
    settings.axis[X_AXIS].jerk = 216000;
    CHECK(settings_override_jerk(X_AXIS, 2));
    CHECK(store_setting(Setting_AxisJerk, "3") == Status_OK);
    CHECK(settings_override_jerk(X_AXIS, 5));
    CHECK(settings_override_jerk(X_AXIS, 0));
    NEAR(settings.axis[X_AXIS].jerk, 648000);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
