#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"

static bool unexpected_write(uint32_t address, uint8_t *data, uint32_t size, bool crc)
{
    (void)address; (void)data; (void)size; (void)crc;
    CHECK(false);
    return false;
}

int main(void)
{
    prepare_initialized_settings(2);
    tool_data_t original = {.tool_id = 2, .radius = 3.5f};
    CHECK(host_save_tool(&original));
    memcpy_to_nvs_ptr saved_writer = hal.nvs.memcpy_to_nvs;
    hal.nvs.memcpy_to_nvs = unexpected_write;
    tool_data_t changed = {.tool_id = 2, .radius = 8.25f, .offset.values = {1, 2, 3}};
    CHECK(grbl.tool_table.set_tool(&changed, false));
    NEAR(grbl.tool_table.get_tool(2)->data->radius, 8.25f);
    NEAR(grbl.tool_table.get_tool(2)->data->offset.values[Z_AXIS], 3);
    hal.nvs.memcpy_to_nvs = saved_writer;
    settings_init();
    NEAR(grbl.tool_table.get_tool(2)->data->radius, 3.5f);
    NEAR(grbl.tool_table.get_tool(2)->data->offset.values[Z_AXIS], 0);
    return EXIT_SUCCESS;
}
