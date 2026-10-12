#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char move[] = "G0X30Y40Z50";
    CHECK(gc_execute_block(move) == Status_OK);
    char g92[] = "G92X10";
    CHECK(gc_execute_block(g92) == Status_OK);
    char tool[] = "G43.1Z5";
    CHECK(gc_execute_block(tool) == Status_OK);
    char set[] = "G10L20P1X2Z3";
    CHECK(gc_execute_block(set) == Status_OK);
    coord_system_data_t stored;
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &stored));
    NEAR(stored.coord.x, 8);
    NEAR(stored.coord.y, 0);
    NEAR(stored.coord.z, 42);
    NEAR(gc_state.position[X_AXIS], 30);
    NEAR(gc_state.position[Z_AXIS], 50);
    return EXIT_SUCCESS;
}
