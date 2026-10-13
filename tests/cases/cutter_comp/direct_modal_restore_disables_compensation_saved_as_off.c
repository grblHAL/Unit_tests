#include "support/cutter_capture_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_cutter_capture();
    CHECK(cutter_block("M70") == Status_OK);
    CHECK(cutter_block("G41.1D6") == Status_OK);
    unsigned before = cutter_enable_calls;
    CHECK(ngc_modal_state_restore());
    CHECK(cutter_enable_calls == before + 1);
    CHECK(cutter_received.side == CComp_Off);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Off);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
