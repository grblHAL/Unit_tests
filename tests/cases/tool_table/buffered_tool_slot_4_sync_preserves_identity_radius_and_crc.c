#include "support/nvs_retry_host.h"
int main(void)
{
    prepare_retry_nvs(false);
    tool_data_t source = {.tool_id = 4, .radius = 3.25f}, result;
    uint32_t address = NVS_ADDR_TOOL_TABLE + 3 * (sizeof(tool_data_t) + NVS_CRC_BYTES);
    CHECK(hal.nvs.memcpy_to_nvs(address, (uint8_t *)&source, sizeof(source), true));
    CHECK(settings_dirty.tool_data == (1u << 3) && settings_dirty.is_dirty);
    nvs_buffer_sync_physical();
    CHECK(physical_writes == 1 && write_address[0] == address && !settings_dirty.is_dirty);
    CHECK(original_nvs.memcpy_from_nvs((uint8_t *)&result, address, sizeof(result), true));
    CHECK(result.tool_id == 4); NEAR(result.radius, 3.25f); nvs_buffer_free();
    return EXIT_SUCCESS;
}
