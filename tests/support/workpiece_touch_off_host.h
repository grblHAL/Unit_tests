#pragma once
#include "support/toolsetter_motion_host.h"
/* A previous reference-tool touch-off at -4 mm is already established. */
static inline void start_workpiece_touch_off(bool fast_pulloff)
{
    prepare_toolsetter_motion(ToolChange_Manual);
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_None, &toolsetter_contact_z, toolsetter_contact));
    sys.tlo_reference_set.mask = Z_AXIS_BIT;
    sys.tlo_reference[Z_AXIS] = -320;
    settings.flags.tool_change_fast_pulloff = fast_pulloff;
    start_manual_change();
    grbl.on_toolchange_ack();
}
static inline status_code_t workpiece_touch_off(void)
{
    char command[] = "$TPW";
    return system_execute_line(command, hal.stream.write);
}
static inline void check_workpiece_touch_off(void)
{
    CHECK(sys.flags.probe_succeeded);
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_EnableDynamic);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS],
         (float)(sys.probe_position[Z_AXIS] - sys.tlo_reference[Z_AXIS]) / settings.axis[Z_AXIS].steps_per_mm);
    CHECK(physical_position[Z_AXIS] == 0);
    CHECK(physical_position[X_AXIS] == 160 && physical_position[Y_AXIS] == 240);
    CHECK(plan_get_current_block() == NULL);
    CHECK(HOST_PARSER_FLAGS.tool_change);
    CHECK(tool_stream_handler != original_enqueue);
    CHECK(!(sys.rt_exec_state & EXEC_CYCLE_START));
}
