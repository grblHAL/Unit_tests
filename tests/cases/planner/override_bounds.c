#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); CHECK(plan_reset()); plan_feed_override(1, 1);
    CHECK(sys.override.feed_rate == MIN_FEED_RATE_OVERRIDE); plan_feed_override(999, 100);
    CHECK(sys.override.feed_rate == MAX_FEED_RATE_OVERRIDE);
    return EXIT_SUCCESS;
}
