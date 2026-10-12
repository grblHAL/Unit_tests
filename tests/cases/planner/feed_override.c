#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); sys.override.feed_rate = 50; CHECK(plan_reset());
    plan_block_t block = {.programmed_rate = 600, .rapid_rate = 1000}; NEAR(plan_compute_profile_nominal_speed(&block), 300);
    block.condition.no_feed_override = 1; NEAR(plan_compute_profile_nominal_speed(&block), 600);
    return EXIT_SUCCESS;
}
