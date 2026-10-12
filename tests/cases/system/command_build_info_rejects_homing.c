#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    state_set(STATE_HOMING);
    CHECK(state_get() == STATE_HOMING);
    CHECK(system_command("$I=Bench controller") == Status_IdleError);
    return EXIT_SUCCESS;
}
