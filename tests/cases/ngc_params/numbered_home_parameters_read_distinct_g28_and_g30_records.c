#include "support/engine_host.h"
#include "ngc_params.h"
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
    return EXIT_SUCCESS;
}
