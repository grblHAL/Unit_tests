#include "support/engine_host.h"
#include "ngc_params.h"
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
    return EXIT_SUCCESS;
}
