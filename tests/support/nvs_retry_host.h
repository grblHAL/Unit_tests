#pragma once
#include "support/engine_host.h"
#include "nvs_buffer.h"
#include "nvs.h"
#include "check.h"
#include <string.h>
static nvs_io_t original_nvs;
static unsigned physical_writes, failed_writes;
static uint32_t write_address[64], write_size[64];
static bool write_checksum[64];
static bool recorded_nvs_write(uint32_t dest, uint8_t *source, uint32_t size, bool checksum)
{
    CHECK(physical_writes < 64);
    write_address[physical_writes] = dest;
    write_size[physical_writes] = size;
    write_checksum[physical_writes++] = checksum;
    if(failed_writes) { failed_writes--; return false; }
    return original_nvs.memcpy_to_nvs(dest, source, size, checksum);
}
static inline nvs_address_t prepare_retry_nvs(bool driver)
{
    engine_prepare();
    hal.nvs.type = NVS_EEPROM;
    hal.nvs.size = GRBL_NVS_SIZE;
    hal.nvs.put_byte(0, SETTINGS_VERSION);
    original_nvs = hal.nvs;
    hal.nvs.memcpy_to_nvs = recorded_nvs_write;
    CHECK(nvs_buffer_alloc());
    nvs_address_t address = driver ? nvs_alloc(32) : 0;
    CHECK(!driver || address != 0);
    CHECK(nvs_buffer_init());
    CHECK(!settings_dirty.is_dirty && physical_writes == 0);
    return address;
}
