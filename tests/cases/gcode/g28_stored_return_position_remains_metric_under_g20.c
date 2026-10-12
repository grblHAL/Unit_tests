#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    coord_system_data_t home = {.coord.values = {-10, -20, -30}};
    settings_write_coord_data(CoordinateSystem_G28, &home);
    char return_home[] = "G20G28";
    CHECK(gc_execute_block(return_home) == Status_OK);
    NEAR(gc_state.position[0], -10);
    NEAR(gc_state.position[1], -20);
    NEAR(gc_state.position[2], -30);
    return EXIT_SUCCESS;
}
