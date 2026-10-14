#include "support/nvs_retry_host.h"

int main(void)
{
    prepare_retry_nvs(false);
    coord_system_data_t first = {.coord.x = 12}, second = {.coord.y = 34}, result;
    settings_write_coord_data(CoordinateSystem_G54, &first);
    settings_write_coord_data(CoordinateSystem_G55, &second);
    failed_writes = 1; nvs_buffer_sync_physical();
    CHECK(physical_writes == 2 && settings_dirty.is_dirty);
    CHECK(settings_dirty.coord_data == (1u << CoordinateSystem_G55));
    nvs_buffer_sync_physical();
    CHECK(physical_writes == 3 && !settings_dirty.is_dirty);
    CHECK(write_address[2] == write_address[0]);
    CHECK(original_nvs.memcpy_from_nvs((uint8_t *)&result, NVS_ADDR_PARAMETERS, sizeof(result), true));
    NEAR(result.coord.x, 12);
    CHECK(original_nvs.memcpy_from_nvs((uint8_t *)&result, NVS_ADDR_PARAMETERS + sizeof(result) + NVS_CRC_BYTES, sizeof(result), true));
    NEAR(result.coord.y, 34); nvs_buffer_free();
    return EXIT_SUCCESS;
}
