#include "support/jog_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_jog_motion(); plan_feed_override(50,100);
    CHECK(system_command("$J=G91X3F100")==Status_OK); plan_block_t *block=plan_get_current_block(); CHECK(block->condition.no_feed_override);
    NEAR(plan_compute_profile_nominal_speed(block),100); finish_jog_motion(); CHECK(axis_pulses[X_AXIS]==240);
    return EXIT_SUCCESS;
}
