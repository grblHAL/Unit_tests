#include "support/nvs_retry_host.h"

int main(void)
{
    engine_prepare(); hal.nvs.type = NVS_EEPROM; hal.nvs.size = GRBL_NVS_SIZE + 1;
    hal.nvs.put_byte(0, SETTINGS_VERSION);
    CHECK(nvs_buffer_alloc() && nvs_buffer_init());
    CHECK(hal.nvs.size % 4 == 0 && hal.nvs.size == GRBL_NVS_SIZE + 4);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
