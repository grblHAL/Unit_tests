#include "support/cutter_capture_host.h"
#include "check.h"

int main(void)
{
    prepare_cutter_capture(); sys.position[X_AXIS] = 800; sync_position();
    CHECK(cutter_block("G41.1D6") == Status_OK); CHECK(cutter_block("G40") == Status_OK);
    NEAR(gc_state.modal.cutter_comp.radius, 3); NEAR(gc_state.position[X_AXIS], 10);
    CHECK(cutter_block("G1X11F100") == Status_CutterCompConflict);
    NEAR(gc_state.position[X_AXIS], 10); CHECK(gc_state.ccomp_off);
    return EXIT_SUCCESS;
}
