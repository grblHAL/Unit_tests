#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    coord_system_data_t original = {.coord.x = 7};
    settings_write_coord_data(CoordinateSystem_G59_1, &original);
    settings.offset_lock.mask = 1;
    char block[] = "G10L2P7X10";
    CHECK(gc_execute_block(block) == Status_GCodeCoordSystemLocked);
    coord_system_data_t stored;
    CHECK(settings_read_coord_data(CoordinateSystem_G59_1, &stored));
    NEAR(stored.coord.x, 7);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    return EXIT_SUCCESS;
}
