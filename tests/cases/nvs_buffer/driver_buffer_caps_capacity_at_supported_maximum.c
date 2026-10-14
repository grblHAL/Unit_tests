#include "support/nvs_retry_host.h"

int main(void)
{
    engine_prepare(); hal.nvs.type = NVS_EEPROM;
    hal.nvs.size_max = NVS_SIZE_MAX + 1024;
    CHECK(nvs_alloc(NVS_SIZE_MAX) == 0);
    CHECK(nvs_alloc(1100) >= GRBL_NVS_SIZE);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
