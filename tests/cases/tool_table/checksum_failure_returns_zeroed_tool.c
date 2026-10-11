#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    tool_data_t written = {.tool_id = 1, .radius = 8};
    CHECK(grbl.tool_table.set_tool(&written));
    uint32_t address = NVS_ADDR_TOOL_TABLE;
    hal.nvs.put_byte(address, hal.nvs.get_byte(address) ^ 1);
    tool_data_t *tool = grbl.tool_table.get_tool(1)->data;
    CHECK(tool && tool->tool_id == 1);
    NEAR(tool->radius, 0.0f);
    return EXIT_SUCCESS;
}
