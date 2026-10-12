#include "support/homing_host.h"
#include "check.h"
static unsigned disable_calls;
static axes_signals_t squared_axes(bool auto_squared) { CHECK(auto_squared); return (axes_signals_t){.mask = X_AXIS_BIT | Y_AXIS_BIT}; }
static void disable_squared(axes_signals_t axes, squaring_mode_t mode) { (void)axes; (void)mode; disable_calls++; }
int main(void)
{
    prepare_homing();
    hal.stepper.get_ganged = squared_axes;
    hal.stepper.disable_motors = disable_squared;
    CHECK(limits_go_home((axes_signals_t){.mask = X_AXIS_BIT | Y_AXIS_BIT}) == Status_IllegalHomingConfiguration);
    CHECK(disable_calls == 0);
    CHECK(wake_calls == 0);
    CHECK(sys.homed.mask == 0);
    return EXIT_SUCCESS;
}
