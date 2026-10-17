#include "support/cutter_capture_host.h"
int main(void)
{
    prepare_cutter_capture();
    CHECK(cutter_block("G41.1D6") == Status_OK);
    motion_mode_t before = gc_state.modal.motion;
    CHECK(cutter_block("G81X10Z-5R1F100") == Status_CutterCompConflict);
    CHECK(gc_state.modal.motion == before);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Left);
    CHECK(cutter_enable_calls == 1 && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
