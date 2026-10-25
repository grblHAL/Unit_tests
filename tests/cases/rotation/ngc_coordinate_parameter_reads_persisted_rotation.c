#include "support/engine_host.h"
#include "ngc_params.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); coord_system_data_t offset={0}; offset.rotation=90*RADDEG;
    offset.coord.values[X_AXIS] = 2;
    settings_write_coord_data(CoordinateSystem_G55,&offset); float value=0;
    CHECK(ngc_param_get(5250,&value)); NEAR(value,90*RADDEG);
    CHECK(ngc_param_get(5241, &value)); NEAR(value, 2);
    CHECK(ngc_param_get(5244, &value)); NEAR(value, 0);
    uint32_t address = NVS_ADDR_PARAMETERS + CoordinateSystem_G55 * (sizeof(offset) + NVS_CRC_BYTES);
    hal.nvs.put_byte(address, hal.nvs.get_byte(address) ^ 1);
    CHECK(ngc_param_get(5250, &value)); NEAR(value, 0);
    coord_system_data_t recovered;
    CHECK(settings_read_coord_data(CoordinateSystem_G55, &recovered));
    NEAR(recovered.rotation, 0); NEAR(recovered.coord.values[X_AXIS], 0);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    settings_write_coord_data(CoordinateSystem_G55, &offset);
    CHECK(ngc_param_get(5250, &value)); NEAR(value, 90 * RADDEG);
    return EXIT_SUCCESS;
}
