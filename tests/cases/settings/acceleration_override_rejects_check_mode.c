#include "support/settings_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(state_get() == STATE_CHECK_MODE);
    CHECK(!settings_override_acceleration(X_AXIS, 25));
    NEAR(settings.axis[X_AXIS].acceleration, 100);
    return EXIT_SUCCESS;
}
