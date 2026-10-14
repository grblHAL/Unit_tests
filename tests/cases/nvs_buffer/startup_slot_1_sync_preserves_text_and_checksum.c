#include "support/nvs_retry_host.h"

int main(void)
{
    prepare_retry_nvs(false);
    stored_line_t line = "G21 G90";
    settings_write_startup_line(1, line);
    CHECK(settings_dirty.startup_lines == (1u << 1));
    nvs_buffer_sync_physical();
    CHECK(physical_writes == 1 && !settings_dirty.is_dirty);
    stored_line_t result;
    uint32_t address = NVS_ADDR_STARTUP_BLOCK + 1 * (sizeof(stored_line_t) + NVS_CRC_BYTES);
    CHECK(write_address[0] == address && !write_checksum[0]);
    CHECK(original_nvs.memcpy_from_nvs((uint8_t *)result, address, sizeof(result), true));
    CHECK(strcmp(result, line) == 0); nvs_buffer_free();
    return EXIT_SUCCESS;
}
