#include "support/engine_host.h"
#include "nvs_buffer.h"
#include "nvs.h"
#include <string.h>
#include "check.h"
static void prepare_buffer(void)
{
    engine_prepare();
    hal.nvs.type = NVS_EEPROM;
    hal.nvs.size = GRBL_NVS_SIZE;
    hal.nvs.put_byte(0, SETTINGS_VERSION);
    CHECK(nvs_buffer_alloc());
    CHECK(nvs_buffer_init());
}

int main(void)
{
    prepare_buffer();
    coord_system_data_t source = {0}, result;
    source.coord.x = 12.5f;
    settings_write_coord_data(CoordinateSystem_G54, &source);
    CHECK(settings_dirty.is_dirty);
    CHECK(settings_dirty.coord_data & 1);
    nvs_buffer_sync_physical();
    CHECK(!settings_dirty.is_dirty);
    CHECK(nvs_buffer_get_physical()->memcpy_from_nvs((uint8_t *)&result, NVS_ADDR_PARAMETERS, sizeof(result), true));
    NEAR(result.coord.x, 12.5f);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
