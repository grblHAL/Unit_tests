#pragma once
#include "support/workpiece_touch_off_host.h"
static unsigned setter_enable_calls, setter_disable_calls, setter_position_calls;
static int32_t setter_hook_contact_z = -240;
static bool disconnected_hand_probe(void *input) { (void)input; return false; }
static bool setter_hook_contact(void *input)
{
    CHECK(input == &setter_hook_contact_z);
    return physical_position[Z_AXIS] <= setter_hook_contact_z;
}
static bool select_fixture_probe(tool_data_t *tool, coord_data_t *position, bool at_fixture, bool on)
{
    if(tool && on) CHECK(tool->tool_id == 3);
    if(position) {
        setter_position_calls++;
        NEAR(position->values[X_AXIS], 1);
        NEAR(position->values[Y_AXIS], 1);
        return false;
    }
    if(!at_fixture) return false;
    if(on) setter_enable_calls++;
    else setter_disable_calls++;
    return hal.probe.select(on ? Probe_Toolsetter : Probe_Default);
}
static inline void prepare_fixture_probe_hook(toolchange_mode_t mode)
{
    prepare_toolsetter_motion(mode);
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_None, NULL, disconnected_hand_probe));
    CHECK(probe_add(Probe_Toolsetter, 1, IRQ_Mode_None, &setter_hook_contact_z, setter_hook_contact));
    grbl.on_probe_toolsetter = select_fixture_probe;
    CHECK(hal.probe.get_state().probe_id == Probe_Default);
}
