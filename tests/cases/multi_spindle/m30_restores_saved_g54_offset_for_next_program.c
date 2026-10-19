#include "support/multi_spindle_program_end_host.h"
int main(void)
{
    prepare_multi_spindle_program_end(true);
    CHECK(spindle_program_block("G10L2P1X3Y4") == Status_OK);
    CHECK(spindle_program_block("G10L2P2X8Y9") == Status_OK);
    CHECK(spindle_program_block("G55") == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G55);
    NEAR(gc_state.modal.g5x_offset.data.coord.values[X_AXIS], 8);
    CHECK(spindle_program_block("M30") == Status_OK);
    check_multi_spindle_program_end(true, ProgramFlow_CompletedM30);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    NEAR(gc_state.modal.g5x_offset.data.coord.values[X_AXIS], 3);
    NEAR(gc_state.modal.g5x_offset.data.coord.values[Y_AXIS], 4);
    return EXIT_SUCCESS;
}
