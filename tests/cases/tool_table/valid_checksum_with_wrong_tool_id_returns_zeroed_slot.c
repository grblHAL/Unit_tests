#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    tool_data_t wrong = {.tool_id = 2, .radius = 9};
    CHECK(hal.nvs.memcpy_to_nvs(NVS_ADDR_TOOL_TABLE, (uint8_t *)&wrong, sizeof(wrong), true) == NVS_TransferResult_OK);
    settings_init();
    tool_data_t *tool = grbl.tool_table.get_tool(1)->data;
    CHECK(tool && tool->tool_id == 1);
    NEAR(tool->radius, 0.0f);
    return EXIT_SUCCESS;
}
