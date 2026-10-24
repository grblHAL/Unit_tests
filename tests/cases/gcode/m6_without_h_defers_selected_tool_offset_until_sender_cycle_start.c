#include "support/m6_program_host.h"

static coolant_state_t read_coolant(void) { return (coolant_state_t){0}; }

static void finish_change(void)
{
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && !HOST_PARSER_FLAGS.tool_change);
    CHECK(gc_state.g43_pending == (tool_id_t)-1);
}

int main(void)
{
    prepare_m6_program();
    hal.coolant.get_state = read_coolant;
    m6_wait_for_ack = true;
    CHECK(m6_block("T1M6G43") == Status_OK);
    CHECK(state_get() == STATE_TOOL_CHANGE && HOST_PARSER_FLAGS.tool_change);
    CHECK(gc_state.tool->tool_id == 0 && gc_state.tool_pending == 1);
    CHECK(gc_state.g43_pending == 1 && m6_changed_calls == 0);
    for(unsigned axis = 0; axis < 3; axis++) NEAR(gc_state.modal.tool_length_offset[axis], 0);
    finish_change();
    CHECK(gc_state.tool == &offset_tool && m6_changed_calls == 1);
    for(unsigned axis = 0; axis < 3; axis++) NEAR(gc_state.modal.tool_length_offset[axis], (float)(axis + 2));
    CHECK(m6_change_calls == 1 && plan_get_current_block() == NULL);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
