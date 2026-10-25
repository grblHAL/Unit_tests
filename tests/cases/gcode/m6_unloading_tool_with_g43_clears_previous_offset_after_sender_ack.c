#include "support/m6_program_host.h"
static coolant_state_t read_coolant(void) { return (coolant_state_t){0}; }
static void finish_change(void)
{
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && !HOST_PARSER_FLAGS.tool_change);
}
int main(void)
{
    prepare_m6_program();
    hal.coolant.get_state = read_coolant;
    m6_wait_for_ack = true;
    for(unsigned axis = 0; axis < 3; axis++) NEAR(grbl.tool_table.get_tool(0)->data->offset.values[axis], 0);
    CHECK(m6_block("T1M6G43H1") == Status_OK);
    finish_change();
    CHECK(gc_state.tool == &offset_tool && gc_state.g43_pending == (tool_id_t)-1);
    for(unsigned axis = 0; axis < 3; axis++) NEAR(gc_state.modal.tool_length_offset[axis], (float)(axis + 2));
    CHECK(m6_block("T0M6G43") == Status_OK);
    CHECK(state_get() == STATE_TOOL_CHANGE && HOST_PARSER_FLAGS.tool_change);
    CHECK(gc_state.tool == &offset_tool && gc_state.g43_pending == 0);
    finish_change();
    CHECK(gc_state.tool->tool_id == 0 && m6_changed_calls == 2 && m6_change_calls == 2);
    float after_ack[3];
    memcpy(after_ack, gc_state.modal.tool_length_offset, sizeof(after_ack));
    CHECK(m6_block("G49") == Status_OK);
    for(unsigned axis = 0; axis < 3; axis++) NEAR(gc_state.modal.tool_length_offset[axis], 0);
    CHECK(gc_state.g43_pending == (tool_id_t)-1 && plan_get_current_block() == NULL);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    if(after_ack[0] != 0 || after_ack[1] != 0 || after_ack[2] != 0)
        fprintf(stderr, "Acknowledged tool0 retained offsets: %.3f %.3f %.3f\n", after_ack[0], after_ack[1], after_ack[2]);
    for(unsigned axis = 0; axis < 3; axis++) NEAR(after_ack[axis], 0);
    return EXIT_SUCCESS;
}
