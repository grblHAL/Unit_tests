#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); sys.override.feed_rate = 200; CHECK(plan_reset());
    plan_block_t block = {.programmed_rate = 1200, .rapid_rate = 1000}; NEAR(plan_compute_profile_nominal_speed(&block), 1000);
    return EXIT_SUCCESS;
}
