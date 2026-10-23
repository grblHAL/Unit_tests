#include "support/engine_host.h"
#include "ngc_params.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    coord_system_data_t saved = {0};
    saved.coord.values[X_AXIS] = 4;
    settings_write_coord_data(CoordinateSystem_G55, &saved);
    sys.probe_coordsys_id = CoordinateSystem_G55;
    sys.probe_position[X_AXIS] = 800;
    gc_state.modal.g5x_offset.data.coord.values[X_AXIS] = 1;
    float value;
    CHECK(ngc_param_get(5061, &value)); NEAR(value, 6);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    uint32_t address = NVS_ADDR_PARAMETERS + CoordinateSystem_G55 * (sizeof(saved) + NVS_CRC_BYTES);
    hal.nvs.put_byte(address, hal.nvs.get_byte(address) ^ 1);
    CHECK(ngc_param_get(5061, &value)); NEAR(value, 0);
    CHECK(sys.probe_coordsys_id == CoordinateSystem_G55);
    CHECK(sys.probe_position[X_AXIS] == 800);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    NEAR(gc_state.modal.g5x_offset.data.coord.values[X_AXIS], 1);
    coord_system_data_t recovered;
    CHECK(settings_read_coord_data(CoordinateSystem_G55, &recovered));
    NEAR(recovered.coord.values[X_AXIS], 0);
    CHECK(ngc_param_get(5061, &value)); NEAR(value, 10);
    settings_write_coord_data(CoordinateSystem_G55, &saved);
    CHECK(ngc_param_get(5061, &value)); NEAR(value, 6);
    return EXIT_SUCCESS;
}
