#include "support/program_end_host.h"
#include "support/malloc_failure_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_program_end(false);
    CHECK(program_block("F120M70") == Status_OK);
    gc_modal_snapshot_t *snapshot = ngc_modal_state_get();
    CHECK(snapshot != NULL);
    CHECK(program_block("G20G91F10") == Status_OK);
    fail_malloc = true;
    CHECK(program_block("M70") == Status_OK);
    fail_malloc = false;
    CHECK(failed_malloc_calls == 0 && ngc_modal_state_get() == snapshot);
    CHECK(program_block("G21G90F20") == Status_OK);
    CHECK(program_block("M72") == Status_OK);
    CHECK(gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 254);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
