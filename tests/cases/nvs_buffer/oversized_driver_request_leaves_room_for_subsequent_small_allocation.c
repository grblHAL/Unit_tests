#include "support/nvs_retry_host.h"

int main(void)
{
    engine_prepare(); hal.nvs.type = NVS_EEPROM; hal.nvs.size = GRBL_NVS_SIZE;
    CHECK(nvs_alloc(NVS_SIZE) == 0);
    CHECK(hal.nvs.driver_area.size == 0 && hal.nvs.size == GRBL_NVS_SIZE);
    nvs_address_t address = nvs_alloc(16);
    CHECK(address == GRBL_NVS_SIZE && hal.nvs.driver_area.size >= 16 + NVS_CRC_BYTES);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
