#include "support/homing_host.h"
#include "check.h"
static axes_signals_t squared_axes(bool auto_squared) { CHECK(auto_squared); return (axes_signals_t){.mask = Y_AXIS_BIT}; }
int main(void)
{
    prepare_homing();
    hal.stepper.get_ganged = squared_axes;
    hal.stepper.disable_motors = NULL;
    CHECK(mc_homing_cycle((axes_signals_t){.mask = X_AXIS_BIT}) == Status_OK);
    CHECK(sys.homed.mask == X_AXIS_BIT);
    CHECK(physical_position[X_AXIS] == 70);
    CHECK(axis_pulses[Y_AXIS] == 0);
    CHECK(homing_success);
    return EXIT_SUCCESS;
}
