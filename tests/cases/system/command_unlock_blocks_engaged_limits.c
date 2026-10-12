#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    state_set(STATE_ALARM);
    settings.limits.flags.hard_enabled = true;
    settings.limits.flags.check_at_init = true;
    command_limits.min.mask = X_AXIS_BIT;
    CHECK(system_command("$X") == Status_LimitsEngaged);
    CHECK(state_get() == STATE_ALARM);
    return EXIT_SUCCESS;
}
