#include "support/engine_host.h"
#include "state_machine.h"
#include "check.h"
static unsigned calls;
static sys_state_t seen;
static void changed(sys_state_t state) { calls++; seen = state; }
int main(void)
{
    engine_prepare();
    grbl.on_state_change = changed;
    state_set(STATE_CHECK_MODE);
    CHECK(calls == 1 && seen == STATE_CHECK_MODE);
    state_set(STATE_CHECK_MODE);
    CHECK(calls == 1);
    state_set(STATE_IDLE);
    CHECK(calls == 2 && seen == STATE_IDLE);
    return EXIT_SUCCESS;
}
