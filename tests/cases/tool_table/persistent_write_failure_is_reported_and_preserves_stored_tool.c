#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"

static unsigned failed_writes;
static bool reject_tool_write(uint32_t address, uint8_t *data, uint32_t size, bool crc)
{
    CHECK(address == NVS_ADDR_TOOL_TABLE + sizeof(tool_data_t) + NVS_CRC_BYTES);
    CHECK(size == sizeof(tool_data_t) && crc);
    CHECK(((tool_data_t *)data)->tool_id == 2);
    failed_writes++;
    return false;
}

int main(void)
{
    prepare_initialized_settings(2);
    tool_data_t original = {.tool_id = 2, .radius = 3.5f};
    CHECK(host_save_tool(&original));
    memcpy_to_nvs_ptr saved_writer = hal.nvs.memcpy_to_nvs;
    hal.nvs.memcpy_to_nvs = reject_tool_write;
    tool_data_t changed = {.tool_id = 2, .radius = 8.25f};
    CHECK(!host_save_tool(&changed));
    CHECK(failed_writes == 1);
    hal.nvs.memcpy_to_nvs = saved_writer;
    settings_init();
    NEAR(grbl.tool_table.get_tool(2)->data->radius, 3.5f);
    return EXIT_SUCCESS;
}
