#include "support/nvs_retry_host.h"

int main(void)
{
    prepare_retry_nvs(false);
    coord_system_data_t source = {.coord.z = 9}, result;
    settings_write_coord_data(CoordinateSystem_G54, &source);
    CHECK(physical_writes == 0 && settings_dirty.is_dirty);
    nvs_buffer_free();
    CHECK(physical_writes == 1);
    CHECK(original_nvs.memcpy_from_nvs((uint8_t *)&result, NVS_ADDR_PARAMETERS, sizeof(result), true));
    NEAR(result.coord.z, 9);
    return EXIT_SUCCESS;
}
