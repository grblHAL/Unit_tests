#include "support/nvs_retry_host.h"

int main(void)
{
    prepare_retry_nvs(false);
    settings.axis[X_AXIS].max_rate = 777; settings_write_global();
    CHECK(settings_dirty.global_settings); failed_writes = 1;
    nvs_buffer_sync_physical();
    CHECK(physical_writes == 1 && settings_dirty.is_dirty && settings_dirty.global_settings);
    nvs_buffer_sync_physical();
    CHECK(physical_writes == 2 && !settings_dirty.is_dirty && !settings_dirty.global_settings);
    CHECK(write_address[1] == NVS_ADDR_GLOBAL && write_size[1] == sizeof(settings_t) + NVS_CRC_BYTES);
    CHECK(!write_checksum[1]);
    settings_t result;
    CHECK(original_nvs.memcpy_from_nvs((uint8_t *)&result, NVS_ADDR_GLOBAL, sizeof(result), true));
    NEAR(result.axis[X_AXIS].max_rate, 777);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
