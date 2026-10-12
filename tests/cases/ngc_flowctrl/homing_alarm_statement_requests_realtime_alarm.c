#include "support/flow_host.h"
#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    state_set(STATE_HOMING);
    CHECK(flow_command(10, "ALARM[6]") == Status_OK);
    CHECK(sys.rt_exec_alarm == Alarm_HomingFailReset);
    CHECK(state_get() == STATE_HOMING);
    CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
