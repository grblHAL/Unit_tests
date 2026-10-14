#include "support/nvs_retry_host.h"

int main(void)
{
    prepare_retry_nvs(false);
    uint8_t version = SETTINGS_VERSION;
    CHECK(hal.nvs.memcpy_to_nvs(0, &version, 1, false)); failed_writes = 1;
    CHECK(settings_dirty.version);
    CHECK(settings_dirty.is_dirty);
    nvs_buffer_sync_physical();
    CHECK(physical_writes == 1 && settings_dirty.version);
    CHECK(settings_dirty.is_dirty);
    nvs_buffer_sync_physical();
    CHECK(physical_writes == 2 && !settings_dirty.version && !settings_dirty.is_dirty);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
