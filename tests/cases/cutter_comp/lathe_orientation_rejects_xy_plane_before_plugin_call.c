#include "support/cutter_capture_host.h"
#include "check.h"

int main(void)
{
    prepare_cutter_capture(); CHECK(cutter_block("G41.1D6L3") == Status_GcodeIllegalPlane);
    CHECK(cutter_enable_calls == 0); CHECK(gc_state.modal.cutter_comp.side == CComp_Off);
    return EXIT_SUCCESS;
}
