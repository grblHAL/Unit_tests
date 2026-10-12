#include "support/jog_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_jog_motion(); prepare_jog_envelope(); sys.soft_limits.mask=AXES_BITMASK;
    CHECK(system_command("$J=G90X-11F100")==Status_TravelExceeded); CHECK(state_get()==STATE_IDLE); CHECK(wake_calls==0);
    CHECK(plan_get_current_block()==NULL); NEAR(gc_state.position[X_AXIS],0); CHECK(axis_pulses[X_AXIS]==0);
    return EXIT_SUCCESS;
}
