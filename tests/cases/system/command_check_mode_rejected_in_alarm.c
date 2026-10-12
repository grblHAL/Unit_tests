#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    state_set(STATE_ALARM);
    CHECK(system_command("$C") == Status_IdleError);
    CHECK(state_get() == STATE_ALARM);
    return EXIT_SUCCESS;
}
