#include "support/jog_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_jog_motion(); CHECK(system_command("$J=G1X1F100")==Status_InvalidJogCommand);
    CHECK(state_get()==STATE_IDLE); CHECK(wake_calls==0); CHECK(plan_get_current_block()==NULL); NEAR(gc_state.position[X_AXIS],0);
    return EXIT_SUCCESS;
}
