#include "support/cutter_capture_host.h"
#include "check.h"

int main(void)
{
    prepare_cutter_capture(); CHECK(cutter_block("G41.1D6") == Status_OK);
    CHECK(cutter_block("G40") == Status_OK);
    CHECK(cutter_enable_calls == 2); CHECK(cutter_received.side == CComp_Off);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Off); CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
