#include "support/jog_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_jog_motion(); CHECK(system_command("$J=G91X1F100")==Status_OK);
    CHECK(system_command("$J=G91X2F100")==Status_OK); CHECK(wake_calls==1); NEAR(gc_state.position[X_AXIS],3);
    CHECK(plan_get_recent_block()->steps.value[X_AXIS]==160); finish_jog_motion(); CHECK(axis_pulses[X_AXIS]==240); CHECK(sys.position[X_AXIS]==240);
    return EXIT_SUCCESS;
}
