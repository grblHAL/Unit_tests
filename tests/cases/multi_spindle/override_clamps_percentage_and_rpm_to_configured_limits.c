#include "support/spindle_override_host.h"
#include "check.h"

int main(void)
{
    spindle_ptrs_t *spindle = prepare_spindle_override();
    RPM_NEAR(spindle_set_override(spindle, 1), 1000);
    CHECK(spindle->param->override_pct == MIN_SPINDLE_RPM_OVERRIDE);
    RPM_NEAR(spindle_set_override(spindle, 65535), 10000);
    CHECK(spindle->param->override_pct == MAX_SPINDLE_RPM_OVERRIDE);
    CHECK(rpm_update_calls == 2);
    return EXIT_SUCCESS;
}
