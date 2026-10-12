#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change();
    start_manual_change();
    grbl.on_toolchange_ack();
    hal.control.interrupt_callback((control_signals_t){.cycle_start = true});
    CHECK(forwarded_controls == 0);
    engine_execute_tasks(STATE_TOOL_CHANGE);
    CHECK(strstr(engine_output, "Perform a probe with $TPW first!") != NULL);
    CHECK(gc_state.tool_change);
    return EXIT_SUCCESS;
}
