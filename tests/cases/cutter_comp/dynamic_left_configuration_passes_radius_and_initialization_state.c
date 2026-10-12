#include "support/cutter_capture_host.h"
#include "check.h"

int main(void)
{
    prepare_cutter_capture(); CHECK(cutter_block("G41.1D6") == Status_OK);
    CHECK(cutter_enable_calls == 1); CHECK(cutter_received.side == CComp_Left && cutter_received.dynamic);
    NEAR(cutter_received.radius, 3); CHECK(gc_state.modal.cutter_comp.side == CComp_Left);
    CHECK(gc_state.modal.cutter_comp.first_move); NEAR(gc_state.modal.cutter_comp.radius, 3);
    return EXIT_SUCCESS;
}
