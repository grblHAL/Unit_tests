#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    sys.probe_coordsys_id = gc_state.modal.g5x_offset.id;
    sys.probe_position[X_AXIS] = 800;
    sys.probe_position[Y_AXIS] = 1600;
    gc_state.modal.g5x_offset.data.coord.values[X_AXIS] = 2;
    gc_state.modal.g5x_offset.data.coord.values[Y_AXIS] = 3;
    float value;
    CHECK(ngc_param_get(5061, &value)); NEAR(value, 8);
    CHECK(ngc_param_get(5062, &value)); NEAR(value, 17);
    CHECK(ngc_param_get(5064, &value)); NEAR(value, 0);
    return EXIT_SUCCESS;
}
