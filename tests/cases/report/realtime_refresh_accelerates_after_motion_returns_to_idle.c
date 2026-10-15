#include "support/status_refresh_host.h"
int main(void)
{
    prepare_refresh_cycle(); next_refresh_report(); next_refresh_report();
    CHECK(hal.stream.report.wco_counter > REPORT_WCO_REFRESH_IDLE_COUNT - 1);
    CHECK(hal.stream.report.override_counter > REPORT_OVERRIDE_REFRESH_IDLE_COUNT - 1);
    finish_motion_pulses(); CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE);
    next_refresh_report();
    CHECK(hal.stream.report.wco_counter <= REPORT_WCO_REFRESH_IDLE_COUNT - 1);
    CHECK(hal.stream.report.override_counter <= REPORT_OVERRIDE_REFRESH_IDLE_COUNT - 1);
    bool wco_seen = false, overrides_seen = false;
    for(unsigned report = 0; report <= REPORT_WCO_REFRESH_IDLE_COUNT + REPORT_OVERRIDE_REFRESH_IDLE_COUNT; report++) {
        next_refresh_report();
        wco_seen |= strstr(engine_output, "|WCO:") != NULL;
        overrides_seen |= strstr(engine_output, "|Ov:") != NULL;
    }
    CHECK(wco_seen && overrides_seen);
    CHECK(physical_position[X_AXIS] == 1600 && axis_pulses[X_AXIS] == 1600);
    return EXIT_SUCCESS;
}
