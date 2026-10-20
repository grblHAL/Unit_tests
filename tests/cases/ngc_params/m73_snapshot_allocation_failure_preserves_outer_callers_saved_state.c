#include "support/program_end_host.h"
#include "support/malloc_failure_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_program_end(false);
    CHECK(program_block("F120M70") == Status_OK);
    gc_modal_snapshot_t *outer = ngc_modal_state_get();
    CHECK(outer != NULL);
    int context;
    CHECK(ngc_call_push(&context));
    CHECK(program_block("G91F45") == Status_OK);
    fail_malloc = true;
    CHECK(program_block("M73") == Status_FlowControlOutOfMemory);
    fail_malloc = false;
    CHECK(failed_malloc_calls == 1 && ngc_modal_state_get() == NULL);
    CHECK(ngc_call_level() == 1 && gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 45);
    (void)ngc_call_pop();
    CHECK(ngc_call_level() == 0 && ngc_modal_state_get() == outer);
    CHECK(program_block("M72") == Status_OK);
    CHECK(!gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 120);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
