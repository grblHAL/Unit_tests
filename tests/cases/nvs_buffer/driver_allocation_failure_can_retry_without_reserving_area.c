#include "support/nvs_allocation_host.h"

int main(void)
{
    prepare_allocation_nvs(); fail_buffer_allocations = 1;
    CHECK(nvs_alloc(16) == 0);
    CHECK(hal.nvs.driver_area.address == 0 && hal.nvs.driver_area.size == 0);
    nvs_address_t address = nvs_alloc(16);
    CHECK(address >= GRBL_NVS_SIZE && address % 4 == 0);
    CHECK(hal.nvs.driver_area.size >= 16 + NVS_CRC_BYTES);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
