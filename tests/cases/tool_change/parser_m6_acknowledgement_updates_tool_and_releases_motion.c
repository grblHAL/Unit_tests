#include "support/tool_change_host.h"

int main(void)
{
    prepare_tool_change();
    install_manual_change_interface();
    char change[] = "T3M6";
    CHECK(gc_execute_block(change) == Status_OK);
    resume_manual_change();
    CHECK(protocol_execute_realtime());
    CHECK(!gc_state.tool_change);
    CHECK(gc_state.tool->tool_id == 3);
    CHECK(manual_tool_changed_calls == 1 && manual_finished_tool == 3);
    CHECK(tool_stream_handler == original_enqueue);
    char move[] = "G1X1F100";
    CHECK(gc_execute_block(move) == Status_OK);
    CHECK(plan_get_current_block() != NULL);
    return EXIT_SUCCESS;
}
