#include "support/nvs_retry_host.h"
int main(void)
{
    prepare_retry_nvs(false);
    tool_data_t first = {.tool_id = 1, .radius = 2}, last = {.tool_id = N_TOOLS, .radius = 4}, result;
    uint32_t address = NVS_ADDR_TOOL_TABLE + (N_TOOLS - 1) * (sizeof(tool_data_t) + NVS_CRC_BYTES);
    CHECK(hal.nvs.memcpy_to_nvs(NVS_ADDR_TOOL_TABLE, (uint8_t *)&first, sizeof(first), true));
    CHECK(hal.nvs.memcpy_to_nvs(address, (uint8_t *)&last, sizeof(last), true));
    failed_writes = 1; nvs_buffer_sync_physical();
    CHECK(physical_writes == 2 && settings_dirty.tool_data == (1u << (N_TOOLS - 1)));
    CHECK(settings_dirty.is_dirty); nvs_buffer_sync_physical();
    CHECK(physical_writes == 3 && write_address[2] == address && !settings_dirty.is_dirty);
    CHECK(original_nvs.memcpy_from_nvs((uint8_t *)&result, address, sizeof(result), true));
    CHECK(result.tool_id == N_TOOLS); NEAR(result.radius, 4); nvs_buffer_free();
    return EXIT_SUCCESS;
}
