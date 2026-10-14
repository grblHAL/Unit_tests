#include "support/nvs_retry_host.h"

int main(void)
{
    nvs_address_t address = prepare_retry_nvs(true);
    uint8_t payload[8] = {1,2,3,4,5,6,7,8}, result[8];
    CHECK(hal.nvs.memcpy_to_nvs(address, payload, sizeof(payload), true));
    CHECK(settings_dirty.driver_settings && settings_dirty.is_dirty);
    failed_writes = 1; nvs_buffer_sync_physical();
    CHECK(settings_dirty.driver_settings && physical_writes == 1);
    nvs_buffer_sync_physical();
    CHECK(!settings_dirty.is_dirty && physical_writes == 2);
    CHECK(write_address[1] == address && write_size[1] == hal.nvs.driver_area.size);
    CHECK(original_nvs.memcpy_from_nvs(result, address, sizeof(result), true));
    CHECK(memcmp(result, payload, sizeof(result)) == 0); nvs_buffer_free();
    return EXIT_SUCCESS;
}
