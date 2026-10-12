#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    state_set(STATE_ALARM);
    sys.alarm = Alarm_ProbeFailContact;
    CHECK(system_command("$X") == Status_OK);
    CHECK(state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
