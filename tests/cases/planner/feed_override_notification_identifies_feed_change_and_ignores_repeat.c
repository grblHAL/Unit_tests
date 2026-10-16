#include "support/engine_host.h"
#include "check.h"
static unsigned notifications;
static void observe_feed_change(override_changed_t kind)
{
    CHECK(kind == OverrideChanged_FeedRate);
    notifications++;
}
int main(void)
{
    engine_prepare();
    CHECK(plan_reset());
    grbl.on_override_changed = observe_feed_change;
    plan_feed_override(50, 100);
    CHECK(notifications == 1 && sys.override.feed_rate == 50 && sys.override.rapid_rate == 100);
    plan_block_t line = {.programmed_rate = 100, .rapid_rate = 1000};
    NEAR(plan_compute_profile_nominal_speed(&line), 50);
    plan_feed_override(50, 100);
    CHECK(notifications == 1);
    return EXIT_SUCCESS;
}
