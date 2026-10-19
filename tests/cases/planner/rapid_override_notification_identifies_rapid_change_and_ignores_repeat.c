#include "support/engine_host.h"
#include "check.h"
static unsigned notifications;
static void observe_rapid_change(override_changed_t kind)
{
    CHECK(kind == OverrideChanged_RapidRate);
    notifications++;
}
int main(void)
{
    engine_prepare();
    CHECK(plan_reset());
    grbl.on_override_changed = observe_rapid_change;
    plan_feed_override(100, 25);
    CHECK(notifications == 1 && sys.override.feed_rate == 100 && sys.override.rapid_rate == 25);
    plan_block_t line = {.programmed_rate = 1000, .rapid_rate = 1000, .condition.rapid_motion = true};
    NEAR(plan_compute_profile_nominal_speed(&line), 250);
    plan_feed_override(100, 25);
    CHECK(notifications == 1);
    return EXIT_SUCCESS;
}
