#include "support/boot_legacy_host.h"

static bool saw_selected_tool;
static void observe_tool_before_reset(void)
{
    if(boot_reads == 3) saw_selected_tool = gc_state.tool->tool_id == 3;
}
int main(void)
{
    boot_program = "T3\n\x18$G\n";
    legacy_read_observer = observe_tool_before_reset;
    run_legacy_boot_program();
    CHECK(saw_selected_tool);
    CHECK(gc_state.tool->tool_id == 0);
    CHECK(boot_setup_calls == 1);
    return EXIT_SUCCESS;
}
