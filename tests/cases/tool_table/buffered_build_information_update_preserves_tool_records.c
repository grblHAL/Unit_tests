#include "support/nvs_retry_host.h"

int main(void)
{
    prepare_retry_nvs(false);
    tool_data_t tool = {.tool_id = 1, .radius = 2.5f}, restored;
    tool.offset.values[X_AXIS] = 1.25f;
    CHECK(hal.nvs.memcpy_to_nvs(NVS_ADDR_TOOL_TABLE, (uint8_t *)&tool, sizeof(tool), true));
    nvs_buffer_sync_physical();
    CHECK(physical_writes == 1 && !settings_dirty.is_dirty);
    char info[] = "machine calibrated";
    CHECK(settings_write_build_info(info));
    CHECK(settings_dirty.build_info && settings_dirty.is_dirty && settings_dirty.tool_data == 0);
    nvs_buffer_sync_physical();
    CHECK(physical_writes == 2 && write_address[1] == NVS_ADDR_BUILD_INFO);
    CHECK(!settings_dirty.is_dirty && settings_dirty.tool_data == 0);
    stored_line_t stored;
    CHECK(original_nvs.memcpy_from_nvs((uint8_t *)stored, NVS_ADDR_BUILD_INFO, sizeof(stored), true));
    CHECK(strcmp(stored, info) == 0);
    CHECK(original_nvs.memcpy_from_nvs((uint8_t *)&restored, NVS_ADDR_TOOL_TABLE, sizeof(restored), true));
    CHECK(restored.tool_id == 1);
    NEAR(restored.radius, 2.5f);
    NEAR(restored.offset.values[X_AXIS], 1.25f);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
