#include "support/spindle_override_host.h"
#include "check.h"

int main(void)
{
    spindle_ptrs_t *spindle = prepare_spindle_override();
    RPM_NEAR(spindle_set_override(spindle, 100), 5000);
    CHECK(rpm_update_calls == 0);
    CHECK(override_event_calls == 0);
    CHECK(!(hal.stream.report.flags.value & Report_Overrides));
    return EXIT_SUCCESS;
}
