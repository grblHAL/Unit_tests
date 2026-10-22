#include "support/cutter_capture_host.h"

int main(void)
{
    prepare_cutter_capture();
    CHECK(cutter_block("G19") == Status_OK);
    CHECK(cutter_block("G41.1D6") == Status_CutterCompConflict);
    CHECK(cutter_enable_calls == 0);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Off);
    CHECK(gc_state.modal.plane_select == PlaneSelect_YZ);
    CHECK(cutter_block("G17G41.1D6") == Status_OK);
    CHECK(cutter_enable_calls == 1);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Left);
    NEAR(gc_state.modal.cutter_comp.radius, 3);
    return EXIT_SUCCESS;
}
