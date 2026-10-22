#include "support/homing_command_host.h"

static homing_get_feedrate_ptr saved_feedrate;
static bool y_available;
static float driver_feedrate(axes_signals_t axes, homing_mode_t mode)
{
    if(axes.mask == Y_AXIS_BIT && mode == HomingMode_Seek && !y_available)
        return 0;
    return saved_feedrate(axes, mode);
}

int main(void)
{
    prepare_homing_command();
    settings.homing.flags.per_axis_feedrates = true;
    settings.axis[Y_AXIS].homing_seek_rate = 200;
    settings.axis[Z_AXIS].homing_seek_rate = 300;
    saved_feedrate = hal.homing.get_feedrate;
    hal.homing.get_feedrate = driver_feedrate;
    CHECK(mc_homing_cycle((axes_signals_t){0}) == Status_Unhandled);
    CHECK(state_get() == STATE_IDLE && completed_calls == 1 && !homing_success);
    CHECK(sys.homed.mask == X_AXIS_BIT);
    CHECK(axis_pulses[X_AXIS] == 110 && physical_position[X_AXIS] == 70);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(plan_get_current_block() == NULL && !sys.abort);
    CHECK(protocol_exec_rt_system());
    y_available = true;
    CHECK(execute_homing_command("$HY") == Status_OK);
    CHECK(state_get() == STATE_IDLE && completed_calls == 2 && homing_success);
    CHECK(sys.homed.mask == (X_AXIS_BIT | Y_AXIS_BIT));
    CHECK(axis_pulses[X_AXIS] == 110 && axis_pulses[Y_AXIS] == 150 && axis_pulses[Z_AXIS] == 0);
    CHECK(physical_position[Y_AXIS] == 110 && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
