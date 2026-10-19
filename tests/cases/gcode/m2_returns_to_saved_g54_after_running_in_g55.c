#include "support/program_end_storage_host.h"
int main(void)
{
    prepare_program_end(false);
    CHECK(program_block("G10L2P1X12Y4") == Status_OK);
    CHECK(program_block("G10L2P2X30Y8") == Status_OK);
    CHECK(program_block("G55") == Status_OK);
    NEAR(gc_state.modal.g5x_offset.data.coord.x, 30);
    CHECK(program_block("M2") == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    NEAR(gc_state.modal.g5x_offset.data.coord.x, 12);
    NEAR(gc_state.modal.g5x_offset.data.coord.y, 4);
    CHECK(program_complete_calls == 1);
    return EXIT_SUCCESS;
}
