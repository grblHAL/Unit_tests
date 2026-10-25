#include "support/engine_host.h"
#include "ngc_params.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    coord_system_data_t first = {0}, second = {0};
    first.coord.values[X_AXIS] = 12;
    first.coord.values[Z_AXIS] = -5;
    second.coord.values[X_AXIS] = 24;
    second.coord.values[Z_AXIS] = -10;
    settings_write_coord_data(CoordinateSystem_G28, &first);
    settings_write_coord_data(CoordinateSystem_G30, &second);
    float value;
    CHECK(ngc_param_get(5161, &value)); NEAR(value, 12);
    CHECK(ngc_param_get(5163, &value)); NEAR(value, -5);
    CHECK(ngc_param_get(5181, &value)); NEAR(value, 24);
    CHECK(ngc_param_get(5183, &value)); NEAR(value, -10);
    CHECK(ngc_param_get(5164, &value)); NEAR(value, 0);
    CHECK(ngc_param_get(5184, &value)); NEAR(value, 0);
    uint32_t g28_address = NVS_ADDR_PARAMETERS + CoordinateSystem_G28 * (sizeof(first) + NVS_CRC_BYTES);
    hal.nvs.put_byte(g28_address, hal.nvs.get_byte(g28_address) ^ 1);
    CHECK(ngc_param_get(5161, &value)); NEAR(value, 0);
    CHECK(ngc_param_get(5181, &value)); NEAR(value, 24);
    coord_system_data_t recovered;
    CHECK(settings_read_coord_data(CoordinateSystem_G28, &recovered));
    NEAR(recovered.coord.values[X_AXIS], 0); NEAR(recovered.coord.values[Z_AXIS], 0);
    settings_write_coord_data(CoordinateSystem_G28, &first);
    CHECK(ngc_param_get(5161, &value)); NEAR(value, 12);
    uint32_t g30_address = NVS_ADDR_PARAMETERS + CoordinateSystem_G30 * (sizeof(second) + NVS_CRC_BYTES);
    hal.nvs.put_byte(g30_address, hal.nvs.get_byte(g30_address) ^ 1);
    CHECK(ngc_param_get(5183, &value)); NEAR(value, 0);
    CHECK(ngc_param_get(5161, &value)); NEAR(value, 12);
    CHECK(settings_read_coord_data(CoordinateSystem_G30, &recovered));
    NEAR(recovered.coord.values[X_AXIS], 0); NEAR(recovered.coord.values[Z_AXIS], 0);
    settings_write_coord_data(CoordinateSystem_G30, &second);
    CHECK(ngc_param_get(5183, &value)); NEAR(value, -10);
    return EXIT_SUCCESS;
}
