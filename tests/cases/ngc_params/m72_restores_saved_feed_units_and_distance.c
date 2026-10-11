#include "support/program_end_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_program_end(false);
    CHECK(program_block("G21G90G94F120") == Status_OK);
    CHECK(program_block("M70") == Status_OK);
    CHECK(program_block("G20G91G93F2") == Status_OK);
    CHECK(program_block("M72") == Status_OK);
    CHECK(!gc_state.modal.units_imperial);
    CHECK(!gc_state.modal.distance_incremental);
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMin);
    NEAR(gc_state.feed_rate, 120.0f);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
