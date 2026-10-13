#include "support/program_end_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_program_end(false);
    hal.coolant_cap.flood = true;
    int context;
    CHECK(ngc_call_push(&context));
    CHECK(program_block("G21G90G17F120M8") == Status_OK);
    CHECK(program_block("M73") == Status_OK);
    CHECK(program_block("G20G91G18F10M9") == Status_OK);
    CHECK(!actual_coolant.flood);
    (void)ngc_call_pop();
    CHECK(ngc_call_level() == 0);
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    NEAR(gc_state.feed_rate, 120);
    CHECK(actual_coolant.flood && gc_state.modal.coolant.flood);
    CHECK(ngc_modal_state_get() == NULL);
    return EXIT_SUCCESS;
}
