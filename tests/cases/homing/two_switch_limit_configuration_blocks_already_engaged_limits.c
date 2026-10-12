#include "support/homing_host.h"
#include "check.h"
static limit_signals_t engaged_limits(void) { return (limit_signals_t){ .min.mask = X_AXIS_BIT }; }
int main(void)
{
    prepare_homing();
    settings.limits.flags.two_switches = true;
    hal.home_cap.a.mask = 0;
    hal.limits.get_state = engaged_limits;
    CHECK(mc_homing_cycle((axes_signals_t){.mask = X_AXIS_BIT}) == Status_Unhandled);
    CHECK(sys.rt_exec_alarm == Alarm_HardLimit);
    CHECK(wake_calls == 0);
    CHECK(sys.homed.mask == 0);
    return EXIT_SUCCESS;
}
