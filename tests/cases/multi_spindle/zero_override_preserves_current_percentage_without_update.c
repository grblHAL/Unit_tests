#include "support/spindle_override_host.h"
#include "check.h"

int main(void)
{
    spindle_ptrs_t *spindle = prepare_spindle_override();
    RPM_NEAR(spindle_set_override(spindle, 120), 6000);
    RPM_NEAR(spindle_set_override(spindle, 0), 6000);
    CHECK(spindle->param->override_pct == 120);
    CHECK(rpm_update_calls == 1);
    CHECK(override_event_calls == 1);
    return EXIT_SUCCESS;
}
