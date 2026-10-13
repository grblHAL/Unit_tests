#include "support/program_end_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_program_end(true);
    CHECK(program_block("G93F12") == Status_OK);
    /* G93 requires a per-block F word; save an explicit inverse-time feed. */
    CHECK(program_block("M70F12") == Status_OK);
    CHECK(program_block("G94F300") == Status_OK);
    CHECK(program_block("M72") == Status_OK);
    CHECK(gc_state.modal.feed_mode == FeedMode_InverseTime);
    NEAR(gc_state.feed_rate, 12);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
