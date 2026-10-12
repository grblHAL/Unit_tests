#include "support/jog_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_jog_motion(); CHECK(system_command("$J=G91X3Y4F100")==Status_OK);
    CHECK(state_get()==STATE_JOG); CHECK(wake_calls==1); plan_block_t *block=plan_get_current_block(); CHECK(block!=NULL);
    CHECK(block->condition.jog_motion); CHECK(block->condition.no_feed_override); CHECK(block->condition.target_validated);
    CHECK(block->steps.value[X_AXIS]==240); CHECK(block->steps.value[Y_AXIS]==320); finish_jog_motion();
    CHECK(axis_pulses[X_AXIS]==240); CHECK(axis_pulses[Y_AXIS]==320); CHECK(physical_position[X_AXIS]==240); CHECK(physical_position[Y_AXIS]==320);
    return EXIT_SUCCESS;
}
