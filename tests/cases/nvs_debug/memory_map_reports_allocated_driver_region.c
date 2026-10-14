#include "support/nvs_debug_host.h"
int main(void)
{
    prepare_nvs_debug(); nvs_address_t address = nvs_alloc(32);
    CHECK(address >= GRBL_NVS_SIZE && address % 4 == 0);
    nvs_memmap(); check_core_memory_map();
    check_map_record("Driver", hal.nvs.driver_area.address, hal.nvs.driver_area.size);
    CHECK(hal.nvs.driver_area.size >= 32 + NVS_CRC_BYTES);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
