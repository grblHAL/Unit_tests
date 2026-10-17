#include "support/tool_wco_observer_host.h"
int main(void)
{
    prepare_tool_wco_observer();
    grbl.on_execute_realtime = tool_motion_foreground;
    for(unsigned axis = 0; axis < N_AXIS; axis++) settings.axis[axis].acceleration = 36000;
    install_manual_change_interface();
    tool_wco_block("T3M6");
    CHECK(gc_state.tool_change);
    tool_wco_block("G10L2P1Z-2");
    CHECK(tool_wco_events == 1 && tool_wco_id == CoordinateSystem_G54);
    NEAR(tool_wco_data.coord.z, -2);
    acknowledge_and_start_tool_change();
    CHECK(protocol_execute_realtime());
    CHECK(!gc_state.tool_change && gc_state.tool->tool_id == 3);
    CHECK(manual_tool_changed_calls == 1 && manual_finished_tool == 3);
    CHECK(tool_stream_handler == original_enqueue);
    CHECK(axis_pulses[Z_AXIS] == 160);
    CHECK(sys.position[Z_AXIS] == -160 && physical_position[Z_AXIS] == -160);
    return EXIT_SUCCESS;
}
