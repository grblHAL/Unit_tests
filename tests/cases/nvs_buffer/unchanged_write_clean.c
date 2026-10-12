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
    coord_system_data_t source = {0};
    source.coord.x = 12.5f;
    settings_write_coord_data(CoordinateSystem_G54, &source);
    nvs_buffer_sync_physical();
    CHECK(!settings_dirty.is_dirty);
    settings_write_coord_data(CoordinateSystem_G54, &source);
    CHECK(!settings_dirty.is_dirty);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
