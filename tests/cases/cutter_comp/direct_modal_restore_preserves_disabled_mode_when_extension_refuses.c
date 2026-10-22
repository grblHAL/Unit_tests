#include "support/cutter_capture_host.h"
#include "ngc_params.h"
int main(void)
{
    prepare_cutter_capture();
    CHECK(cutter_block("G41.1D6") == Status_OK);
    CHECK(cutter_block("M70") == Status_OK);
    CHECK(cutter_block("G40") == Status_OK);
    CHECK(cutter_block("G1X10F100") == Status_OK);
    cutter_accept = false;
    unsigned before = cutter_enable_calls;
    CHECK(cutter_block("M72") == Status_GcodeUnsupportedCommand);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Off);
    CHECK(cutter_enable_calls == before + 1);
    bool restored = ngc_modal_state_restore();
    CHECK(cutter_enable_calls == before + 2 && cutter_received.side == CComp_Left);
    bool refused_restore_kept_disabled = gc_state.modal.cutter_comp.side == CComp_Off;
    fprintf(stderr, "Refused direct restore: result=%u, parser compensation side=%u\n",
            restored, (unsigned)gc_state.modal.cutter_comp.side);
    cutter_accept = true;
    CHECK(cutter_block("G40") == Status_OK);
    CHECK(cutter_block("G1X20F100") == Status_OK);
    CHECK(ngc_modal_state_restore());
    CHECK(cutter_received.side == CComp_Left);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Left);
    NEAR(gc_state.modal.cutter_comp.radius, 3);
    ngc_modal_state_invalidate();
    CHECK(refused_restore_kept_disabled);
    return EXIT_SUCCESS;
}
