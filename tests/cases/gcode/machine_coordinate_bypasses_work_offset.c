#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    coord_system_data_t offset = {0};
    offset.coord.x = 10;
    settings_write_coord_data(CoordinateSystem_G55, &offset);
    char select[] = "G55";
    CHECK(gc_execute_block(select) == Status_OK);
    char block[] = "G53G0X2";
    CHECK(gc_execute_block(block) == Status_OK);
    NEAR(gc_state.position[X_AXIS], 2);
    return EXIT_SUCCESS;
}
