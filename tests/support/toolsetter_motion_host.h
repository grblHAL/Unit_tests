#pragma once
#include "support/tool_change_host.h"
#include "probe.h"
static int32_t toolsetter_contact_z = -240;
static unsigned toolsetter_xy_pulses;
static inline bool toolsetter_contact(void *input)
{
    CHECK(input == &toolsetter_contact_z);
    return sys.position[Z_AXIS] <= toolsetter_contact_z;
}
static void toolsetter_safe_pulse(stepper_t *stepper)
{
    if(stepper->step_out.mask & (X_AXIS_BIT | Y_AXIS_BIT)) {
        CHECK(physical_position[Z_AXIS] == 0);
        toolsetter_xy_pulses++;
    }
    pulse_driver(stepper);
}
static inline void prepare_toolsetter_motion(toolchange_mode_t mode)
{
    prepare_tool_change_motion();
    settings.tool_change.mode = mode;
    settings.tool_change.seek_rate = 100;
    settings.tool_change.feed_rate = 20;
    settings.tool_change.pulloff_rate = 100;
    settings.tool_change.probing_distance = 10;
    sys.homed.mask = X_AXIS_BIT | Y_AXIS_BIT | Z_AXIS_BIT;
    sys.work_envelope.min.z = -200;
    sys.work_envelope.max.z = 0;
    coord_system_data_t fixture = {.coord = {.x = 1, .y = 1, .z = -2}};
    settings_write_coord_data(CoordinateSystem_G59_3, &fixture);
    hal.stepper.pulse_start = toolsetter_safe_pulse;
}
static inline void run_automatic_toolsetter(void)
{
    start_manual_change();
    grbl.on_toolchange_ack();
    CHECK(tool_stream_handler(CMD_CYCLE_START));
    engine_execute_tasks(STATE_TOOL_CHANGE);
}
