#include "support/nvs_debug_host.h"
int main(void)
{
    prepare_nvs_debug(); nvs_memmap(); check_core_memory_map();
    check_map_record("Driver", 0, 0);
    CHECK(NVS_ADDR_PARAMETERS >= NVS_ADDR_GLOBAL + sizeof(settings_t) + NVS_CRC_BYTES);
    return EXIT_SUCCESS;
}
