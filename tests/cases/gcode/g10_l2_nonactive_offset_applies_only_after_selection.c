#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char set[] = "G10L2P2X10";
    CHECK(gc_execute_block(set) == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    NEAR(gc_state.modal.g5x_offset.data.coord.x, 0);
    char move[] = "G55G0X1";
    CHECK(gc_execute_block(move) == Status_OK);
    NEAR(gc_state.position[X_AXIS], 11);
    return EXIT_SUCCESS;
}
