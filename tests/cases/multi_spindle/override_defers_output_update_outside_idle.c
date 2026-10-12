#include "support/spindle_override_host.h"
#include "check.h"

int main(void)
{
    spindle_ptrs_t *spindle = prepare_spindle_override();
    state_set(STATE_CHECK_MODE);
    CHECK(state_get() == STATE_CHECK_MODE);
    sys.step_control.update_spindle_rpm = false;
    RPM_NEAR(spindle_set_override(spindle, 150), 7500);
    CHECK(rpm_update_calls == 0);
    CHECK(sys.step_control.update_spindle_rpm);
    CHECK(override_event_calls == 1);
    return EXIT_SUCCESS;
}
