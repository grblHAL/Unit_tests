#include "support/nvs_flash_host.h"

int main(void)
{
    prepare_flash_nvs(); nvs_buffer_sync_physical();
    CHECK(flash_writes == 0 && !settings_dirty.is_dirty); nvs_buffer_free();
    return EXIT_SUCCESS;
}
