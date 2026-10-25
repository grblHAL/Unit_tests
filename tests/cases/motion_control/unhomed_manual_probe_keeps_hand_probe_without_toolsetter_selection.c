#include "support/probe_motion_host.h"

static unsigned setter_calls, start_calls;
static bool select_toolsetter(tool_data_t *tool, coord_data_t *position, bool at_fixture, bool on)
{
    (void)tool; (void)position; (void)at_fixture; (void)on;
    setter_calls++;
    return true;
}
static bool observe_probe_start(axes_signals_t axes, float *target, plan_line_data_t *data)
{
    CHECK(axes.mask == Z_AXIS_BIT);
    NEAR(target[Z_AXIS], 1);
    CHECK(!data->condition.probing_toolsetter);
    start_calls++;
    return true;
}

int main(void)
{
    prepare_probe_motion();
    contact_axis = Z_AXIS;
    grbl.on_probe_toolsetter = select_toolsetter;
    grbl.on_probe_start = observe_probe_start;
    CHECK(sys.homed.mask == 0);
    char command[] = "G38.2Z1F100";
    CHECK(gc_execute_block(command) == Status_OK);
    CHECK(start_calls == 1 && setter_calls == 0 && completed_calls == 1);
    CHECK(sys.flags.probe_succeeded && sys.probe_position[Z_AXIS] == 40);
    /* Contact is latched before the axis finishes decelerating. */
    CHECK(physical_position[Z_AXIS] >= 40 && physical_position[Z_AXIS] < 80);
    CHECK(sys.position[Z_AXIS] == physical_position[Z_AXIS]);
    CHECK(axis_pulses[Z_AXIS] == (unsigned)physical_position[Z_AXIS]);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0);
    CHECK(sys.homed.mask == 0 && !hal.probe.get_state().is_probing);
    CHECK(!sys.abort && sys.alarm == Alarm_None && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
