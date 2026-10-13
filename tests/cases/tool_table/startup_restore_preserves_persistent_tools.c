#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    tool_data_t written = {.tool_id = 2, .radius = 4};
    CHECK(host_save_tool(&written));
    settings_restore((settings_restore_t){.startup_lines = true});
    tool_data_t *tool = grbl.tool_table.get_tool(2)->data;
    CHECK(tool && tool->tool_id == 2);
    NEAR(tool->radius, 4.0f);
    return EXIT_SUCCESS;
}
