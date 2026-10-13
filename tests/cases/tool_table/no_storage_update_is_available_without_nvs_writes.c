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
    hal.nvs.type = NVS_None;
    hal.nvs.memcpy_to_nvs = unexpected_write;
    tool_data_t tool = {.tool_id = 4, .radius = 6.5f, .offset.values = {1, 2, 3}};
    CHECK(host_save_tool(&tool));
    tool_table_entry_t *entry = grbl.tool_table.get_tool(4);
    CHECK(entry->data && entry->data->tool_id == 4 && entry->pocket == 4);
    NEAR(entry->data->radius, 6.5f);
    NEAR(entry->data->offset.values[Z_AXIS], 3);
    return EXIT_SUCCESS;
}
