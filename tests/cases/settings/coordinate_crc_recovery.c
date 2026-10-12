#include "support/engine_host.h"
#include "nvs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_prepare();
    coord_system_data_t source = {0}, result;
    source.coord.x = 12;
    settings_write_coord_data(CoordinateSystem_G54, &source);
    uint32_t address = NVS_ADDR_PARAMETERS + CoordinateSystem_G54 * (sizeof(source) + NVS_CRC_BYTES);
    hal.nvs.put_byte(address, hal.nvs.get_byte(address) ^ 1);
    CHECK(!settings_read_coord_data(CoordinateSystem_G54, &result));
    for(unsigned i = 0; i < N_AXIS; i++) CHECK(result.coord.values[i] == 0);
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &result));
    CHECK(result.coord.x == 0);
    return EXIT_SUCCESS;
}
