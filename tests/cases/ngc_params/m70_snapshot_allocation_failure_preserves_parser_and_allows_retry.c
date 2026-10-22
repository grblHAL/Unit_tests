#include "support/program_end_host.h"
#include "support/malloc_failure_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_program_end(false);
    CHECK(program_block("G20G91F10") == Status_OK);
    fail_malloc = true;
    CHECK(program_block("M70") == Status_FlowControlOutOfMemory);
    fail_malloc = false;
    CHECK(failed_malloc_calls == 1 && ngc_modal_state_get() == NULL);
    CHECK(gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 254);
    CHECK(plan_get_current_block() == NULL);
    CHECK(program_block("M70") == Status_OK);
    CHECK(program_block("G21G90F20") == Status_OK);
    CHECK(program_block("M72") == Status_OK);
    CHECK(gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 254);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
