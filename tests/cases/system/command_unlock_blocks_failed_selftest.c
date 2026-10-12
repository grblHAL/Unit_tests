#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    state_set(STATE_ALARM);
    sys.alarm = Alarm_SelftestFailed;
    CHECK(system_command("$X") == Status_SelfTestFailed);
    CHECK(state_get() == STATE_ALARM);
    return EXIT_SUCCESS;
}
