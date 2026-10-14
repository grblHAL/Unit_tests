#include "support/nvs_retry_host.h"

int main(void)
{
    nvs_address_t driver = prepare_retry_nvs(true);
    uint32_t address = driver + hal.nvs.driver_area.size + 4;
    uint8_t payload[4] = {9,8,7,6}, result[4];
    CHECK(hal.nvs.memcpy_to_nvs(address, payload, sizeof(payload), true));
    CHECK(physical_writes == 1 && write_address[0] == address && write_checksum[0]);
    CHECK(!settings_dirty.is_dirty);
    CHECK(hal.nvs.memcpy_from_nvs(result, address, sizeof(result), true));
    CHECK(memcmp(result, payload, sizeof(result)) == 0); nvs_buffer_free();
    return EXIT_SUCCESS;
}
