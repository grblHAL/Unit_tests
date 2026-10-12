#include "support/engine_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    state_set(STATE_CHECK_MODE);
    state_set(STATE_SAFETY_DOOR);
    CHECK(state_get() == STATE_CHECK_MODE);
    return EXIT_SUCCESS;
}
