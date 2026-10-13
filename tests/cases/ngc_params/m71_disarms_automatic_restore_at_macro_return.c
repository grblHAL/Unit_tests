#include "support/program_end_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_program_end(true);
    int context;
    CHECK(ngc_call_push(&context));
    CHECK(program_block("G21G90F120M73") == Status_OK);
    CHECK(program_block("G20G91F10") == Status_OK);
    CHECK(program_block("M71") == Status_OK);
    CHECK(ngc_modal_state_get() == NULL);
    (void)ngc_call_pop();
    CHECK(ngc_call_level() == 0);
    CHECK(gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 254);
    return EXIT_SUCCESS;
}
