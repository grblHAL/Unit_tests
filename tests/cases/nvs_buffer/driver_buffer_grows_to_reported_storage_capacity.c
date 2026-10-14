#include "support/nvs_retry_host.h"

int main(void)
{
    engine_prepare(); hal.nvs.type = NVS_EEPROM;
    hal.nvs.size_max = NVS_SIZE_MAX;
    nvs_address_t first = nvs_alloc(1100), second = nvs_alloc(1100);
    CHECK(first >= GRBL_NVS_SIZE && second >= first + 1100 + NVS_CRC_BYTES);
    CHECK(second % 4 == 0 && hal.nvs.size > NVS_SIZE && hal.nvs.size <= NVS_SIZE_MAX);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
