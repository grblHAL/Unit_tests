#include "support/engine_host.h"
#include "ngc_params.h"
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
    return EXIT_SUCCESS;
}
