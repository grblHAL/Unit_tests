#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); gc_state.offset_id = 3; sys.soft_limits.mask = 1; sys.override.control.feed_rates_disable = 1;
    plan_line_data_t data; memset(&data, 0xFF, sizeof(data)); plan_data_init(&data);
    CHECK(data.offset_id == 3); CHECK(data.spindle.hal == gc_spindle_get(-1)->hal);
    CHECK(data.condition.no_feed_override); CHECK(!data.condition.target_validated); NEAR(data.feed_rate, 0); CHECK(data.message == NULL);
    return EXIT_SUCCESS;
}
