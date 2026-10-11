#include "support/sync_parser_host.h"
#include "check.h"

int main(void)
{
    prepare_sync_parser();
    sync_feedback.rpm = 500;
    CHECK(css_block("G76Z10P1I1J0.2K1H2") == Status_OK);
    NEAR(gc_state.position[Z_AXIS], 10.0f);
    CHECK(plan_get_current_block() == NULL);
    CHECK(!sys.override.control.feed_rates_disable);
    CHECK(!sys.override.control.spindle_rpm_disable);
    return EXIT_SUCCESS;
}
