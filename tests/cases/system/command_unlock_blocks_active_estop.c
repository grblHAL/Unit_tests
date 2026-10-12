#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    state_set(STATE_ALARM);
    command_controls.e_stop = true;
    CHECK(system_command("$X") == Status_EStop);
    CHECK(state_get() == STATE_ALARM);
    return EXIT_SUCCESS;
}
