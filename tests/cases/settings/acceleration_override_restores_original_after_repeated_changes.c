#include "support/settings_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    state_set(STATE_IDLE);
    settings.axis[X_AXIS].acceleration = 12345;
    CHECK(settings_override_acceleration(X_AXIS, 25));
    CHECK(settings_override_acceleration(X_AXIS, 50));
    CHECK(settings_override_acceleration(X_AXIS, 0));
    NEAR(settings.axis[X_AXIS].acceleration, 12345);
    return EXIT_SUCCESS;
}
