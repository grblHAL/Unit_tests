#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); sys.override.rapid_rate = 25; CHECK(plan_reset());
    plan_block_t block = {.programmed_rate = 1000, .rapid_rate = 1000, .condition.rapid_motion = 1}; NEAR(plan_compute_profile_nominal_speed(&block), 250);
    return EXIT_SUCCESS;
}
