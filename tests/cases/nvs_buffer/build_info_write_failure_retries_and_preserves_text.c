#include "support/nvs_retry_host.h"

int main(void)
{
    prepare_retry_nvs(false);
    stored_line_t line = "machine identity"; CHECK(settings_write_build_info(line));
    CHECK(settings_dirty.build_info); failed_writes = 1;
    nvs_buffer_sync_physical();
    CHECK(physical_writes == 1 && settings_dirty.is_dirty && settings_dirty.build_info);
    nvs_buffer_sync_physical();
    CHECK(physical_writes == 2 && !settings_dirty.is_dirty && !settings_dirty.build_info);
    CHECK(write_address[1] == NVS_ADDR_BUILD_INFO && write_size[1] == sizeof(stored_line_t) + NVS_CRC_BYTES);
    CHECK(!write_checksum[1]);
    stored_line_t result;
    CHECK(original_nvs.memcpy_from_nvs((uint8_t *)&result, NVS_ADDR_BUILD_INFO, sizeof(result), true));
    CHECK(strcmp(result, "machine identity") == 0);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
