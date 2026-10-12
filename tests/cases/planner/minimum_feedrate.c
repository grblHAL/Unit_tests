#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); CHECK(plan_reset());
    plan_block_t block = {.programmed_rate = 0, .rapid_rate = 1000}; NEAR(plan_compute_profile_nominal_speed(&block), MINIMUM_FEED_RATE);
    return EXIT_SUCCESS;
}
