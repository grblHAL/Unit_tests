#include "support/settings_initialized_host.h"

int main(void)
{
    prepare_initialized_settings(2);
    tool_data_t stored = {.tool_id = 2, .radius = 2.5f};
    CHECK(host_save_tool(&stored));
    settings.flags.tool_persistent = false;
    settings.tool_id = 2;
    sys.cold_start = true;
    gc_init(false);
    CHECK(gc_state.tool->tool_id == 0);
    NEAR(gc_state.tool->radius, 0);
    NEAR(grbl.tool_table.get_tool(2)->data->radius, 2.5f);
    return EXIT_SUCCESS;
}
