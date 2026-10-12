#include "support/jog_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_jog_motion(); prepare_jog_envelope(); settings.limits.flags.jog_soft_limited=true;
    CHECK(system_command("$J=G91X-20Y-10F100")==Status_OK); NEAR(gc_state.position[X_AXIS],-10); NEAR(gc_state.position[Y_AXIS],-5);
    plan_block_t *block=plan_get_current_block(); NEAR(block->target_mm[X_AXIS],-10); NEAR(block->target_mm[Y_AXIS],-5);
    finish_jog_motion(); CHECK(physical_position[X_AXIS]==-800); CHECK(physical_position[Y_AXIS]==-400);
    CHECK(axis_pulses[X_AXIS]==800); CHECK(axis_pulses[Y_AXIS]==400);
    return EXIT_SUCCESS;
}
