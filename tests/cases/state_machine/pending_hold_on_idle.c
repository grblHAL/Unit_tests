#include "support/engine_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    state_set(STATE_CHECK_MODE);
    sys.flags.feed_hold_pending = true;
    state_set(STATE_IDLE);
    CHECK(sys.rt_exec_state & EXEC_FEED_HOLD);
    return EXIT_SUCCESS;
}
