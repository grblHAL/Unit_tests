#include "support/nvs_retry_host.h"

int main(void)
{
    prepare_retry_nvs(false);
    uint8_t version = SETTINGS_VERSION;
    CHECK(hal.nvs.memcpy_to_nvs(0, &version, 1, false));
    CHECK(settings_dirty.version && settings_dirty.is_dirty);
    nvs_buffer_sync_physical();
    CHECK(physical_writes == 1 && write_address[0] == 0 && write_size[0] == 1);
    CHECK(!settings_dirty.version && !settings_dirty.is_dirty);
    CHECK(original_nvs.get_byte(0) == version);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
