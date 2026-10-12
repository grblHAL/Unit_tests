#include "support/cutter_capture_host.h"
#include "check.h"

int main(void)
{
    prepare_cutter_capture(); cutter_accept = false;
    CHECK(cutter_block("G41.1D6") == Status_GcodeUnsupportedCommand);
    CHECK(cutter_enable_calls == 1); CHECK(cutter_received.side == CComp_Left);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Off); NEAR(gc_state.modal.cutter_comp.radius, 0);
    return EXIT_SUCCESS;
}
