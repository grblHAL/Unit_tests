#include "support/homing_host.h"
#include "check.h"
static axes_signals_t squared_axes(bool auto_squared) { CHECK(auto_squared); return (axes_signals_t){.mask = X_AXIS_BIT}; }
int main(void)
{
    prepare_homing();
    hal.stepper.get_ganged = squared_axes;
    hal.stepper.disable_motors = NULL;
    CHECK(limits_go_home((axes_signals_t){.mask = X_AXIS_BIT}) == Status_IllegalHomingConfiguration);
    CHECK(wake_calls == 0);
    CHECK(sys.homed.mask == 0);
    return EXIT_SUCCESS;
}
