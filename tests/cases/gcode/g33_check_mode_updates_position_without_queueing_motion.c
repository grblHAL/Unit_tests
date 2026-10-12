#include "support/sync_parser_host.h"
#include "check.h"

int main(void)
{
    prepare_sync_parser();
    CHECK(css_block("G33Z1K0.1") == Status_OK);
    NEAR(gc_state.position[Z_AXIS], 1.0f);
    NEAR(gc_state.distance_per_rev, 0.1f);
    CHECK(plan_get_current_block() == NULL);
    CHECK(!sys.override.control.feed_rates_disable);
    CHECK(!sys.override.control.spindle_rpm_disable);
    return EXIT_SUCCESS;
}
