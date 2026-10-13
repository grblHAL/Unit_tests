#include "support/named_parameter_host.h"

int main(void)
{
    engine_parser_prepare();
    coord_system_data_t saved = {0};
    saved.coord.values[X_AXIS] = 3;
    saved.coord.values[Y_AXIS] = -4;
    settings_write_coord_data(CoordinateSystem_G92, &saved);
    settings.flags.g92_is_volatile = true;
    sys.cold_start = true;
    gc_init(false);
    NEAR(gc_state.g92_offset.coord.values[X_AXIS], 0);
    NEAR(gc_state.g92_offset.coord.values[Y_AXIS], 0);
    NEAR(read_named_parameter("_x"), 0);
    NEAR(read_named_parameter("_y"), 0);
    return EXIT_SUCCESS;
}
