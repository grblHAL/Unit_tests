#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    coord_system_data_t offset = {0};
    offset.coord.x = 10;
    offset.coord.y = -5;
    settings_write_coord_data(CoordinateSystem_G55, &offset);
    char block[] = "G55G0X2Y3";
    CHECK(gc_execute_block(block) == Status_OK);
    NEAR(gc_state.position[X_AXIS], 12);
    NEAR(gc_state.position[Y_AXIS], -2);
    return EXIT_SUCCESS;
}
