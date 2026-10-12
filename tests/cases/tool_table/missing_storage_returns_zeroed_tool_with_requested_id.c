#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    hal.nvs.type = NVS_None;
    tool_data_t *tool = grbl.tool_table.get_tool(3)->data;
    CHECK(tool && tool->tool_id == 3);
    NEAR(tool->radius, 0.0f);
    NEAR(tool->offset.values[0], 0.0f);
    return EXIT_SUCCESS;
}
