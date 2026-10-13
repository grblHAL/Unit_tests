#include "support/program_end_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_program_end(true);
    int outer, inner;
    CHECK(ngc_call_push(&outer));
    CHECK(program_block("G21G90G17F120M73") == Status_OK);
    CHECK(program_block("G20G91G18F10") == Status_OK);
    CHECK(ngc_call_push(&inner));
    CHECK(program_block("M73") == Status_OK);
    CHECK(program_block("G21G90G19F400") == Status_OK);
    (void)ngc_call_pop();
    CHECK(ngc_call_level() == 1);
    CHECK(gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);
    NEAR(gc_state.feed_rate, 254);
    CHECK(ngc_modal_state_get() && ngc_modal_state_get()->modal.auto_restore);
    (void)ngc_call_pop();
    CHECK(ngc_call_level() == 0);
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    NEAR(gc_state.feed_rate, 120);
    CHECK(ngc_modal_state_get() == NULL);
    return EXIT_SUCCESS;
}
