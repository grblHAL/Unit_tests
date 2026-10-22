#include "support/program_end_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_program_end(false);
    plan_feed_override(80, 50);
    CHECK(program_block("M70") == Status_OK);
    plan_feed_override(65, 25);
    CHECK(program_block("M72") == Status_OK);
    unsigned feed = sys.override.feed_rate, rapid = sys.override.rapid_rate;
    CHECK(!sys.override.control.feed_rates_disable);
    CHECK(!gc_state.modal.override_ctrl.feed_rates_disable);
    ngc_modal_state_invalidate();
    fprintf(stderr, "M72 with unchanged enable flags: feed=%u rapid=%u; expected80/50\n", feed, rapid);
    CHECK(feed == 80 && rapid == 50);
    return EXIT_SUCCESS;
}
