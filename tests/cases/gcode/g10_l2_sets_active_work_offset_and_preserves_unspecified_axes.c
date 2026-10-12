#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char block[] = "G10L2P1X10Y20";
    CHECK(gc_execute_block(block) == Status_OK);
    coord_system_data_t stored;
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &stored));
    NEAR(stored.coord.x, 10);
    NEAR(stored.coord.y, 20);
    NEAR(stored.coord.z, 0);
    NEAR(gc_state.modal.g5x_offset.data.coord.x, 10);
    NEAR(gc_state.position[X_AXIS], 0);
    return EXIT_SUCCESS;
}
