#include "support/tool_change_host.h"
#include "check.h"
int main(void)
{
    prepare_tool_change();
    install_manual_change_interface();
    grbl.on_execute_realtime = tool_motion_foreground;
    char change[] = "T3M6";
    CHECK(gc_execute_block(change) == Status_OK);
    CHECK(state_get() == STATE_TOOL_CHANGE && HOST_PARSER_FLAGS.tool_change);
    CHECK(gc_state.tool->tool_id == 0);
    char jog[] = "$J=G91X1F100";
    CHECK(system_execute_line(jog, hal.stream.write) == Status_OK);
    CHECK(state_get() == STATE_JOG);
    for(unsigned ticks = 0; ticks < 100000 && state_get() == STATE_JOG; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        CHECK(protocol_exec_rt_system());
    }
    CHECK(state_get() == STATE_TOOL_CHANGE && HOST_PARSER_FLAGS.tool_change);
    CHECK(physical_position[X_AXIS] == 80 && sys.position[X_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 80 && gc_state.tool->tool_id == 0);
    CHECK(manual_tool_changed_calls == 0 && plan_get_current_block() == NULL);
    resume_manual_change();
    CHECK(protocol_execute_realtime());
    CHECK(!HOST_PARSER_FLAGS.tool_change && gc_state.tool->tool_id == 3);
    CHECK(manual_tool_changed_calls == 1 && manual_finished_tool == 3);
    CHECK(tool_stream_handler == original_enqueue && hal.control.interrupt_callback == original_control);
    return EXIT_SUCCESS;
}
