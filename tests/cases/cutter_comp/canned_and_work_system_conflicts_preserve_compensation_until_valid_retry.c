#include "support/cutter_capture_host.h"
int main(void)
{
    prepare_cutter_capture();
    CHECK(cutter_block("G10L2P2X5") == Status_OK);
    CHECK(cutter_block("G81Z-1R0.5F100") == Status_OK);
    CHECK(gc_state.modal.canned_cycle_active);
    CHECK(cutter_block("G41.1D6") == Status_CutterCompConflict);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Off && cutter_enable_calls == 0);
    CHECK(gc_state.modal.canned_cycle_active);
    CHECK(cutter_block("G80") == Status_OK);
    CHECK(cutter_block("G41.1D6") == Status_OK);
    unsigned before = cutter_enable_calls;
    CHECK(cutter_block("G55") == Status_CutterCompConflict);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    NEAR(gc_state.modal.g5x_offset.data.coord.values[X_AXIS], 0);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Left && cutter_enable_calls == before);
    CHECK(cutter_block("G40") == Status_OK);
    CHECK(cutter_block("G1X10F100") == Status_OK);
    CHECK(cutter_block("G55") == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G55);
    NEAR(gc_state.modal.g5x_offset.data.coord.values[X_AXIS], 5);
    return EXIT_SUCCESS;
}
