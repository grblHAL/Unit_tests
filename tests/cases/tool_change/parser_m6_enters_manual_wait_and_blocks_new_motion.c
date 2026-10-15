#include "support/tool_change_host.h"

int main(void)
{
    prepare_tool_change();
    install_manual_change_interface();
    char change[] = "T3M6";
    CHECK(gc_execute_block(change) == Status_OK);
    CHECK(gc_state.tool_change && state_get() == STATE_TOOL_CHANGE);
    CHECK(select_calls == 1 && selected_next && selected_tool->tool_id == 3);
    char move[] = "G1X1F100";
    CHECK(gc_execute_block(move) == Status_GcodeToolChangePending);
    CHECK(plan_get_current_block() == NULL && wake_calls == 0);
    hal.driver_reset();
    CHECK(!gc_state.tool_change);
    return EXIT_SUCCESS;
}
