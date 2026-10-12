#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    sys.blocking_event = true;
    CHECK(system_command("$C") == Status_NotAllowedCriticalEvent);
    CHECK(state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
