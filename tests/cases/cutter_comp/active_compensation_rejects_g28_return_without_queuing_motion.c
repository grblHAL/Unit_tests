#include "support/cutter_capture_host.h"
int main(void)
{
    prepare_cutter_capture();
    CHECK(cutter_block("G41.1D6") == Status_OK);
    CHECK(cutter_block("G28X10") == Status_CutterCompConflict);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Left);
    NEAR(gc_state.position[X_AXIS], 0);
    CHECK(cutter_enable_calls == 1 && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
