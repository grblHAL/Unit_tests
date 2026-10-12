#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char select[] = "G55";
    CHECK(gc_execute_block(select) == Status_OK);
    char set[] = "G10L2P0X12";
    CHECK(gc_execute_block(set) == Status_OK);
    coord_system_data_t stored;
    CHECK(settings_read_coord_data(CoordinateSystem_G55, &stored));
    NEAR(stored.coord.x, 12);
    NEAR(gc_state.modal.g5x_offset.data.coord.x, 12);
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &stored));
    NEAR(stored.coord.x, 0);
    return EXIT_SUCCESS;
}
