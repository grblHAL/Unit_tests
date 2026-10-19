#include "support/cutter_capture_host.h"
int main(void)
{
    prepare_cutter_capture();
    CHECK(cutter_block("G41.1D6") == Status_OK);
    CHECK(cutter_block("G10L2P1X4") == Status_OK);
    coord_system_data_t saved;
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &saved));
    NEAR(saved.coord.values[X_AXIS], 4);
    NEAR(gc_state.modal.g5x_offset.data.coord.values[X_AXIS], 4);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Left);
    NEAR(gc_state.modal.cutter_comp.radius, 3);
    CHECK(cutter_enable_calls == 1 && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
