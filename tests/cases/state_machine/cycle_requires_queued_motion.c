#include "support/engine_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(plan_reset());
    state_set(STATE_IDLE);
    state_set(STATE_CYCLE);
    CHECK(state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
