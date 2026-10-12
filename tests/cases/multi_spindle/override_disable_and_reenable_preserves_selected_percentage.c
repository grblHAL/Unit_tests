#include "support/spindle_override_host.h"
#include "check.h"

int main(void)
{
    spindle_ptrs_t *spindle = prepare_spindle_override();
    RPM_NEAR(spindle_set_override(spindle, 120), 6000);
    CHECK(spindle_override_disable(spindle, true));
    RPM_NEAR(driver_rpm, 5000);
    CHECK(spindle->param->override_pct == 120);
    CHECK(spindle->param->state.override_disable);
    CHECK(!spindle_override_disable(spindle, false));
    RPM_NEAR(driver_rpm, 6000);
    CHECK(!spindle->param->state.override_disable);
    CHECK(rpm_update_calls == 3);
    CHECK(override_event_calls == 3);
    return EXIT_SUCCESS;
}
