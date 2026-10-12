#include "support/canned_motion_host.h"
#include "check.h"
static unsigned wco_calls;
static void observe_wco(void)
{
    wco_calls++;
    CHECK(plan_get_current_block() != NULL);
    CHECK(physical_position[X_AXIS] == 0);
}
int main(void)
{
    prepare_canned_motion();
    settings.status_report.sync_on_wco_change = false;
    CHECK(canned_block("G1X1F100") == Status_OK);
    CHECK(plan_get_current_block() != NULL);
    hal.stream.report.flags.value = 0;
    grbl.on_wco_changed = observe_wco;
    system_flag_wco_change();
    CHECK(wco_calls == 1);
    CHECK(hal.stream.report.flags.value & Report_WCO);
    CHECK(axis_pulses[X_AXIS] == 0);
    return EXIT_SUCCESS;
}
