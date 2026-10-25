#include "support/cutter_capture_host.h"
#include "state_machine.h"
static unsigned suspend_calls;
static bool suspend_sender(bool suspend) { suspend_calls++; return suspend; }
static atc_status_t no_automatic_changer(void) { return ATC_None; }
int main(void)
{
    prepare_cutter_capture();
    CHECK(state_get() == STATE_CHECK_MODE);
    settings.tool_change.mode = ToolChange_Manual;
    hal.stream.suspend_read = suspend_sender;
    hal.tool.atc_get_state = no_automatic_changer;
    tool_id_t current_tool = gc_state.tool->tool_id;
    CHECK(current_tool != 2);
    CHECK(cutter_block("G41.1D6") == Status_OK);
    CHECK(cutter_block("T2M6") == Status_CutterCompConflict);
    CHECK(gc_state.tool->tool_id == current_tool);
    CHECK(suspend_calls == 0 && !HOST_PARSER_FLAGS.tool_change);
    CHECK(cutter_enable_calls == 1 && plan_get_current_block() == NULL);
    CHECK(cutter_block("G40") == Status_OK);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Off);
    CHECK(cutter_block("T2M6") == Status_OK);
    CHECK(gc_state.tool->tool_id == current_tool);
    CHECK(suspend_calls == 0 && !HOST_PARSER_FLAGS.tool_change);
    CHECK(cutter_enable_calls == 2 && plan_get_current_block() == NULL);
    CHECK(state_get() == STATE_CHECK_MODE);
    return EXIT_SUCCESS;
}
