#pragma once
#include "support/program_end_host.h"
#include "support/settings_host.h"
#include "nvs.h"
static unsigned end_g92_saves;
static inline void corrupt_end_coordinate(coord_system_id_t id)
{
    uint32_t crc = NVS_ADDR_PARAMETERS + id * (sizeof(coord_system_data_t) + NVS_CRC_BYTES) + sizeof(coord_system_data_t);
    hal.nvs.put_byte(crc, hal.nvs.get_byte(crc) ^ 1);
}
static inline coord_system_data_t read_end_coordinate(coord_system_id_t id)
{
    coord_system_data_t data;
    CHECK(settings_read_coord_data(id, &data));
    return data;
}
static inline void record_end_coordinate(coord_system_id_t id, coord_system_data_t *data)
{ CHECK(data != NULL); if(id == CoordinateSystem_G92) end_g92_saves++; }
