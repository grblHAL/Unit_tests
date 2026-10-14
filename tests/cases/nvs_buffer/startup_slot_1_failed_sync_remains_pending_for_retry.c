#include "support/nvs_retry_host.h"

int main(void)
{
    prepare_retry_nvs(false);
    stored_line_t line = "G21 G90";
    settings_write_startup_line(1, line); failed_writes = 1;
    nvs_buffer_sync_physical();
    CHECK(physical_writes == 1);
    fprintf(stderr, "startup pending mask=%u, dirty=%u after rejected physical write\n", settings_dirty.startup_lines, settings_dirty.is_dirty);
    CHECK(settings_dirty.startup_lines == (1u << 1) && settings_dirty.is_dirty);
    nvs_buffer_sync_physical();
    CHECK(physical_writes == 2 && !settings_dirty.is_dirty);
    stored_line_t result;
    uint32_t address = NVS_ADDR_STARTUP_BLOCK + 1 * (sizeof(stored_line_t) + NVS_CRC_BYTES);
    CHECK(original_nvs.memcpy_from_nvs((uint8_t *)result, address, sizeof(result), true));
    CHECK(strcmp(result, line) == 0); nvs_buffer_free();
    return EXIT_SUCCESS;
}
