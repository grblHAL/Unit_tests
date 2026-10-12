#include "support/cutter_capture_host.h"
#include "check.h"

int main(void)
{
    prepare_cutter_capture(); CHECK(cutter_block("G20G41.1D0.25") == Status_OK);
    CHECK(cutter_enable_calls == 1); NEAR(cutter_received.radius, 3.175f);
    NEAR(gc_state.modal.cutter_comp.radius, 3.175f); CHECK(gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
