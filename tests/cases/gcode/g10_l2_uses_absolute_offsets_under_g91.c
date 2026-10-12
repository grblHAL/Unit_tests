#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char move[] = "G0X30";
    CHECK(gc_execute_block(move) == Status_OK);
    char set[] = "G91G10L2P1X10";
    CHECK(gc_execute_block(set) == Status_OK);
    coord_system_data_t stored;
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &stored));
    NEAR(stored.coord.x, 10);
    NEAR(gc_state.position[X_AXIS], 30);
    CHECK(gc_state.modal.distance_incremental);
    return EXIT_SUCCESS;
}
