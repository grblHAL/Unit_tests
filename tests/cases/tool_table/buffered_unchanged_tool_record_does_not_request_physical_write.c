#include "support/nvs_retry_host.h"
int main(void)
{
    prepare_retry_nvs(false);
    tool_data_t source = {.tool_id = 1, .radius = 2};
    CHECK(hal.nvs.memcpy_to_nvs(NVS_ADDR_TOOL_TABLE, (uint8_t *)&source, sizeof(source), true));
    nvs_buffer_sync_physical(); CHECK(physical_writes == 1);
    CHECK(hal.nvs.memcpy_to_nvs(NVS_ADDR_TOOL_TABLE, (uint8_t *)&source, sizeof(source), true));
    CHECK(!settings_dirty.is_dirty && settings_dirty.tool_data == 0);
    nvs_buffer_sync_physical(); CHECK(physical_writes == 1); nvs_buffer_free();
    return EXIT_SUCCESS;
}
