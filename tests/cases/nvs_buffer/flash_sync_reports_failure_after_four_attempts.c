#include "support/nvs_flash_host.h"

int main(void)
{
    prepare_flash_nvs();
    coord_system_data_t source = {.coord.x = 23};
    settings_write_coord_data(CoordinateSystem_G54, &source);
    flash_failures = 4; nvs_buffer_sync_physical();
    CHECK(flash_writes == 4);
    CHECK(strstr(engine_output, "Settings write failed!") != NULL);
    coord_system_data_t result;
    memcpy(&result, flash_image + NVS_ADDR_PARAMETERS, sizeof(result));
    NEAR(result.coord.x, 0); nvs_buffer_free();
    return EXIT_SUCCESS;
}
