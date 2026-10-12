#include "support/cutter_capture_host.h"
#include "check.h"

int main(void)
{
    prepare_cutter_capture(); CHECK(cutter_block("G18") == Status_OK);
    CHECK(cutter_block("G41.1D6L3") == Status_OK);
    CHECK(cutter_enable_calls == 1); CHECK(cutter_received.orientation == ToolPos3_315);
    CHECK(gc_state.modal.cutter_comp.orientation == ToolPos3_315);
    CHECK(cutter_received_plane.axis_0 == Z_AXIS && cutter_received_plane.axis_1 == X_AXIS);
    return EXIT_SUCCESS;
}
