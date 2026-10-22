#include "support/homing_command_host.h"
#include "check.h"
static axes_signals_t squared_axes(bool auto_squared) { CHECK(auto_squared); return (axes_signals_t){.mask = X_AXIS_BIT}; }
int main(void)
{
    prepare_homing_command();
    hal.stepper.get_ganged = squared_axes;
    hal.stepper.disable_motors = NULL;
    CHECK(limits_go_home((axes_signals_t){.mask = X_AXIS_BIT}) == Status_IllegalHomingConfiguration);
    CHECK(wake_calls == 0);
    CHECK(sys.homed.mask == 0);
    CHECK(execute_homing_command("$H") == Status_IllegalHomingConfiguration);
    CHECK(state_get() == STATE_IDLE);
    CHECK(completed_calls == 1 && !homing_success);
    CHECK(wake_calls == 0 && sys.homed.mask == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(axis_pulses[axis] == 0);

    CHECK(protocol_exec_rt_system());
    hal.stepper.get_ganged = NULL;
    CHECK(execute_homing_command("$H") == Status_OK);
    CHECK(state_get() == STATE_IDLE);
    CHECK(completed_calls == 2 && homing_success);
    CHECK(sys.homed.mask == AXES_BITMASK);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == -10);
        CHECK(physical_position[axis] == switch_position[axis] - 10);
        CHECK(axis_pulses[axis] == (unsigned)switch_position[axis] + 30);
    }
    return EXIT_SUCCESS;
}
