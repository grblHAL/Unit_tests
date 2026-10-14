#include "support/nvs_retry_host.h"

int main(void)
{
    engine_prepare(); hal.nvs.type = NVS_EEPROM; hal.nvs.size = GRBL_NVS_SIZE;
    hal.nvs.put_byte(0, SETTINGS_VERSION);
    coord_system_data_t source = {.coord.x = 45}, result;
    settings_write_coord_data(CoordinateSystem_G54, &source);
    CHECK(nvs_buffer_alloc() && nvs_buffer_init());
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &result));
    NEAR(result.coord.x, 45); CHECK(!settings_dirty.is_dirty); nvs_buffer_free();
    return EXIT_SUCCESS;
}
