#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    coord_system_data_t home28 = {.coord.values = {-10, -20, -30}};
    coord_system_data_t home30 = {.coord.values = {11, 22, 33}};
    settings_write_coord_data(CoordinateSystem_G28, &home28);
    settings_write_coord_data(CoordinateSystem_G30, &home30);
    char return_home[] = "G30";
    CHECK(gc_execute_block(return_home) == Status_OK);
    NEAR(gc_state.position[0], 11);
    NEAR(gc_state.position[1], 22);
    NEAR(gc_state.position[2], 33);
    return EXIT_SUCCESS;
}
