#include "support/tool_wco_observer_host.h"
static bool tool_door_open;
static control_signals_t tool_door_controls(void)
{
    return (control_signals_t){.safety_door_ajar = tool_door_open};
}
int main(void)
{
    prepare_tool_wco_observer();
    install_manual_change_interface();
    hal.control.get_state = tool_door_controls;
    hal.signals_cap.safety_door_ajar = true;
    tool_wco_block("T3M6");
    tool_wco_block("G10L2P1Z0");
    tool_door_open = true;
    acknowledge_and_start_tool_change();
    CHECK(!gc_state.tool_change);
    CHECK(sys.rt_exec_state & EXEC_SAFETY_DOOR);
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_SAFETY_DOOR);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(tool_stream_handler == original_enqueue);
    CHECK(plan_get_current_block() == NULL);
    tool_door_open = false;
    system_set_exec_state_flag(EXEC_DOOR_CLOSED);
    CHECK(protocol_exec_rt_system());
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    for(unsigned service = 0; service < 100 && state_get() != STATE_IDLE; service++)
        CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE);
    fprintf(stderr, "resumed tool=%u notifications=%u pending=%u\n", (unsigned)gc_state.tool->tool_id, manual_tool_changed_calls, (unsigned)gc_state.tool_change);
    CHECK(gc_state.tool->tool_id == 3 && manual_tool_changed_calls == 1);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
