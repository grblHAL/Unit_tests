#include "support/m6_program_host.h"
#include "check.h"

int main(void)
{
    prepare_m6_program();
    m6_wait_for_ack = true;
    CHECK(m6_block("T1M6G43H1") == Status_OK);
    CHECK(state_get() == STATE_TOOL_CHANGE && HOST_PARSER_FLAGS.tool_change);
    CHECK(gc_state.tool->tool_id == 0 && gc_state.g43_pending == 1);
    CHECK(m6_changed_calls == 0);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 0);
    HOST_PARSER_FLAGS.tool_change = false;
    state_update(EXEC_CYCLE_START);
    CHECK(state_get() == STATE_IDLE);
    CHECK(sys.rt_exec_state & EXEC_STATUS_REPORT);
    CHECK(gc_state.tool == &offset_tool);
    CHECK(m6_changed_calls == 1 && m6_changed_tool == &offset_tool);
    CHECK(gc_state.g43_pending == (tool_id_t)-1);
    NEAR(gc_state.modal.tool_length_offset[X_AXIS], 2);
    NEAR(gc_state.modal.tool_length_offset[Y_AXIS], 3);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 4);
    return EXIT_SUCCESS;
}
