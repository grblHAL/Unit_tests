#include "support/flow_host.h"
#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    sys.driver_started = true;
    engine_output[0] = '\0';
    CHECK(flow_command(10, "ALARM[4]") == Status_OK);
    CHECK(sys.alarm == Alarm_ProbeFailInitial);
    CHECK(state_get() == STATE_ALARM);
    CHECK(strcmp(engine_output, "ALARM:4" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
