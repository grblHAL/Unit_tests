#include "support/flow_host.h"
#include "support/system_command_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(ngc_param_set(1, 2));
    CHECK(flow_command(10, "ALARM[#1+2]") == Status_OK);
    CHECK(sys.alarm == Alarm_ProbeFailInitial);
    CHECK(state_get() == STATE_ALARM);
    return EXIT_SUCCESS;
}
