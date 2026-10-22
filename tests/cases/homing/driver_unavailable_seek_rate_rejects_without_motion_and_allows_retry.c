#include "support/homing_command_host.h"

static homing_get_feedrate_ptr original_feedrate;
static bool seek_available;
static float driver_feedrate(axes_signals_t axes, homing_mode_t mode)
{
    if(!seek_available && axes.mask == Y_AXIS_BIT && mode == HomingMode_Seek)
        return 0.0f;
    return original_feedrate(axes, mode);
}
int main(void)
{
    prepare_homing_command();
    original_feedrate = hal.homing.get_feedrate;
    hal.homing.get_feedrate = driver_feedrate;
    CHECK(mc_homing_cycle((axes_signals_t){.mask = Y_AXIS_BIT}) == Status_Unhandled);
    CHECK(state_get() == STATE_IDLE);
    CHECK(completed_calls == 1 && !homing_success);
    CHECK(wake_calls == 0 && sys.homed.mask == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(axis_pulses[axis] == 0);
    CHECK(protocol_exec_rt_system());

    seek_available = true;
    CHECK(execute_homing_command("$HY") == Status_OK);
    CHECK(state_get() == STATE_IDLE);
    CHECK(completed_calls == 2 && homing_success);
    CHECK(sys.homed.mask == Y_AXIS_BIT);
    CHECK(sys.position[Y_AXIS] == -10 && physical_position[Y_AXIS] == 110);
    CHECK(axis_pulses[Y_AXIS] == 150);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
