#pragma once
#include "support/settings_host.h"
#include "nvs_buffer.h"
#include "nvs.h"
#include "report.h"
#include "config.h"
static nvs_io_t defaults_physical;
static unsigned defaults_failures, defaults_writes, defaults_imports;
static uint8_t defaults_flash[NVS_SIZE];
static status_code_t defaults_status(status_code_t status)
{
    CHECK(status == Status_SettingReadFail); defaults_failures++; return status;
}
static bool defaults_write(uint32_t address, uint8_t *data, uint32_t size, bool checksum)
{
    defaults_writes++;
    return defaults_physical.memcpy_to_nvs(address, data, size, checksum);
}
static bool defaults_flash_read(uint8_t *data)
{ defaults_imports++; memcpy(data, defaults_flash, GRBL_NVS_SIZE); return true; }
static bool defaults_flash_write(uint8_t *data)
{ defaults_writes++; memcpy(defaults_flash, data, GRBL_NVS_SIZE); return true; }
static inline void prepare_defaults_storage(nvs_type type)
{
    prepare_settings_store(); report_init_fns();
    defaults_physical = hal.nvs;
    hal.nvs.type = type; hal.nvs.size = GRBL_NVS_SIZE;
    grbl.report.status_message = defaults_status;
    hal.nvs.memcpy_to_nvs = defaults_write;
    if(type == NVS_Flash) {
        hal.nvs.memcpy_from_nvs = NULL; hal.nvs.memcpy_to_nvs = NULL;
        hal.nvs.memcpy_from_flash = defaults_flash_read;
        hal.nvs.memcpy_to_flash = defaults_flash_write;
    } else if(type == NVS_None) {
        hal.nvs.memcpy_from_nvs = NULL; hal.nvs.memcpy_to_nvs = NULL;
    }
    settings.arc_tolerance = 9;
    CHECK(nvs_buffer_alloc());
}
static inline void check_restored_storage_defaults(void)
{
    CHECK(hal.nvs.type == NVS_Emulated);
    CHECK(hal.nvs.get_byte(0) == SETTINGS_VERSION);
    NEAR(settings.arc_tolerance, DEFAULT_ARC_TOLERANCE);
    coord_system_data_t coordinate;
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &coordinate));
    NEAR(coordinate.coord.x, 0); NEAR(coordinate.coord.y, 0); NEAR(coordinate.coord.z, 0);
    stored_line_t startup;
    CHECK(settings_read_startup_line(0, startup)); CHECK(startup[0] == 0);
    CHECK(!settings_dirty.is_dirty); CHECK(change_callbacks == 1);
}
