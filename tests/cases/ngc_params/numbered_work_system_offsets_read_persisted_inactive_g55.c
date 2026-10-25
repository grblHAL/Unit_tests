#include "support/engine_host.h"
#include "ngc_params.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    coord_system_data_t offsets = {.coord.values = {2, 3, 4}};
    settings_write_coord_data(CoordinateSystem_G55, &offsets);
    float value;
    CHECK(ngc_param_get(5241, &value)); NEAR(value, 2);
    CHECK(ngc_param_get(5242, &value)); NEAR(value, 3);
    CHECK(ngc_param_get(5243, &value)); NEAR(value, 4);
    CHECK(ngc_param_get(5244, &value)); NEAR(value, 0);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    CHECK(!ngc_param_set(5241, 99));
    CHECK(ngc_param_get(5241, &value)); NEAR(value, 2);
    uint32_t address = NVS_ADDR_PARAMETERS + CoordinateSystem_G55 * (sizeof(offsets) + NVS_CRC_BYTES);
    hal.nvs.put_byte(address, hal.nvs.get_byte(address) ^ 1);
    CHECK(ngc_param_get(5241, &value)); NEAR(value, 0);
    coord_system_data_t recovered;
    CHECK(settings_read_coord_data(CoordinateSystem_G55, &recovered));
    NEAR(recovered.coord.values[X_AXIS], 0);
    NEAR(recovered.coord.values[Z_AXIS], 0);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    settings_write_coord_data(CoordinateSystem_G55, &offsets);
    CHECK(ngc_param_get(5243, &value)); NEAR(value, 4);
    return EXIT_SUCCESS;
}
