#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    coord_system_data_t home = {.coord.values = {-10, -20, -30}};
    settings_write_coord_data(CoordinateSystem_G28, &home);
    char work[] = "G10L2P1X100";
    CHECK(gc_execute_block(work) == Status_OK);
    char g92[] = "G92X5";
    CHECK(gc_execute_block(g92) == Status_OK);
    char return_home[] = "G28";
    CHECK(gc_execute_block(return_home) == Status_OK);
    NEAR(gc_state.position[0], -10);
    NEAR(gc_state.position[1], -20);
    NEAR(gc_state.position[2], -30);
    return EXIT_SUCCESS;
}
