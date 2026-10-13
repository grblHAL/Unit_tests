#include "support/program_end_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_program_end(false);
    plan_feed_override(80, 50);
    CHECK(program_block("M70") == Status_OK);
    CHECK(program_block("M50P0") == Status_OK);
    CHECK(gc_state.modal.override_ctrl.feed_rates_disable);
    plan_feed_override(110, 100);
    CHECK(ngc_modal_state_restore());
    CHECK(!gc_state.modal.override_ctrl.feed_rates_disable);
    CHECK(!sys.override.control.feed_rates_disable);
    CHECK(sys.override.feed_rate == 80 && sys.override.rapid_rate == 50);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
