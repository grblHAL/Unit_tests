#include "seal_host.h"
int main(void)
{
    seal_start();
    sys_state_t states[] = {STATE_HOMING, STATE_CYCLE, STATE_JOG, STATE_TOOL_CHANGE};
    for (unsigned i = 0; i < 4; i++)
    {
        seal_state(states[i]);
        CHECK(solenoid && !timer && output_port == 0);
    }
    CHECK(claims == 1 && saves == 1);
    return 0;
}
