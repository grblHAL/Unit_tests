#include "support/autosquare_homing_host.h"
static home_signals_t stuck_squared_switches(void)
{
    return (home_signals_t){.a = {.mask = X_AXIS_BIT}, .b = {.mask = X_AXIS_BIT}};
}

int main(void)
{
    prepare_autosquare_homing();
    squared_primary = 80; squared_secondary = 120;
    hal.homing.get_state = stuck_squared_switches;
    CHECK(mc_homing_cycle((axes_signals_t){.mask = X_AXIS_BIT}) == Status_Unhandled);
    CHECK(sys.alarm == Alarm_FailPulloff);
    CHECK(sys.homed.mask == 0 && !homing_success);
    CHECK(reset_calls == 1);
    CHECK(squared_primary < 80 && squared_secondary < 120);
    return EXIT_SUCCESS;
}
