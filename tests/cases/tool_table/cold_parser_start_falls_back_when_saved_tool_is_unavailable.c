#include "support/settings_initialized_host.h"

int main(void)
{
    prepare_initialized_settings(2);
    settings.flags.tool_persistent = true;
    settings.tool_id = 5;
    CHECK(grbl.tool_table.get_tool(5)->data == NULL);
    sys.cold_start = true;
    gc_init(false);
    CHECK(gc_state.tool != NULL);
    CHECK(gc_state.tool->tool_id == 0);
    NEAR(gc_state.tool->radius, 0);
    return EXIT_SUCCESS;
}
