#include "support/settings_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    state_set(STATE_IDLE);
    CHECK(settings_override_acceleration(X_AXIS, 25));
    NEAR(settings.axis[X_AXIS].acceleration, 90000);
    NEAR(settings.axis[Y_AXIS].acceleration, 100);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
