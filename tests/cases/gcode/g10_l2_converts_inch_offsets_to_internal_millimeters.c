#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char block[] = "G20G10L2P1X1";
    CHECK(gc_execute_block(block) == Status_OK);
    coord_system_data_t stored;
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &stored));
    NEAR(stored.coord.x, 25.4f);
    NEAR(gc_state.modal.g5x_offset.data.coord.x, 25.4f);
    return EXIT_SUCCESS;
}
