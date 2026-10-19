#pragma once
#include "support/probe_motion_host.h"
#if TOOL_LENGTH_OFFSET_AXIS < X_AXIS || TOOL_LENGTH_OFFSET_AXIS > Z_AXIS
#error This case requires a configured fixed tool-offset axis
#endif
static inline void probe_then_set_fixed_axis_reference(void)
{
    contact_axis = TOOL_LENGTH_OFFSET_AXIS;
    prepare_probe_motion();
    char plane[4], probe[32], reference[] = "$TLR";
    strcpy(plane, TOOL_LENGTH_OFFSET_AXIS == X_AXIS ? "G17" : "G19");
    snprintf(probe, sizeof(probe), "G38.2%c1F100", *axis_letter[TOOL_LENGTH_OFFSET_AXIS]);
    CHECK(gc_execute_block(plane) == Status_OK);
    CHECK(gc_execute_block(probe) == Status_OK);
    CHECK(sys.flags.probe_succeeded && completed_calls == 1);
    CHECK(sys.probe_position[TOOL_LENGTH_OFFSET_AXIS] == 40);
    CHECK(system_execute_line(reference, hal.stream.write) == Status_OK);
    CHECK(sys.tlo_reference_set.mask == bit(TOOL_LENGTH_OFFSET_AXIS));
    CHECK(memcmp(sys.tlo_reference, sys.probe_position, sizeof(sys.probe_position)) == 0);
    CHECK(gc_state.modal.plane_select == (TOOL_LENGTH_OFFSET_AXIS == X_AXIS ? PlaneSelect_XY : PlaneSelect_YZ));
    CHECK(hal.stream.report.flags.value & Report_TLOReference);
    CHECK(sys.alarm == Alarm_None && plan_get_current_block() == NULL);
}
