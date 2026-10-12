#include "support/engine_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    state_set(STATE_HOMING);
    CHECK(state_get() == STATE_HOMING);
    CHECK(sys.flags.is_homing);
    state_set(STATE_IDLE);
    CHECK(!sys.flags.is_homing);
    return EXIT_SUCCESS;
}
