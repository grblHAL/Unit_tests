#include "support/program_end_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_program_end(false);
    CHECK(program_block("F120") == Status_OK);
    sys.override.feed_rate = 80;
    sys.override.rapid_rate = 50;
    CHECK(program_block("M70") == Status_OK);
    gc_modal_snapshot_t *snapshot = ngc_modal_state_get();
    CHECK(snapshot != NULL);
    NEAR(snapshot->modal.feed_rate, 120.0f);
    CHECK(snapshot->override.feed_rate == 80);
    CHECK(snapshot->override.rapid_rate == 50);
    CHECK(!snapshot->modal.auto_restore);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
