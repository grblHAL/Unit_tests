#include "support/flow_host.h"
#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    sys.driver_started = true;
    CHECK(flow_command(10, "IF[0]") == Status_OK);
    engine_output[0] = '\0';
    CHECK(flow_command(10, "ALARM[4]") == Status_OK);
    CHECK(sys.alarm == Alarm_None);
    CHECK(state_get() == STATE_IDLE);
    CHECK(engine_output[0] == '\0');
    CHECK(flow_command(10, "ENDIF") == Status_OK);
    return EXIT_SUCCESS;
}
