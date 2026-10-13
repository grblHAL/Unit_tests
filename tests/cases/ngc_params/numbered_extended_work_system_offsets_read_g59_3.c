#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    coord_system_data_t offsets = {.coord.values = {1.25f, 2.5f, 3.75f}};
    settings_write_coord_data(CoordinateSystem_G59_3, &offsets);
    float value;
    CHECK(ngc_param_get(5381, &value)); NEAR(value, 1.25f);
    CHECK(ngc_param_get(5382, &value)); NEAR(value, 2.5f);
    CHECK(ngc_param_get(5383, &value)); NEAR(value, 3.75f);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    return EXIT_SUCCESS;
}
