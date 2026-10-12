#include "support/coolant_host.h"
#include "override.h"
#include "check.h"

int main(void)
{
    prepare_coolant(); hal.coolant_cap.flood = true; sys.override_delay.coolant = true;
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_COOLANT_FLOOD_TOGGLE));
    CHECK(protocol_exec_rt_system()); CHECK(!actual_coolant.flood); CHECK(coolant_calls == 0);
    sys.override_delay.coolant = false;
    CHECK(protocol_exec_rt_system()); CHECK(actual_coolant.flood); CHECK(coolant_calls == 1);
    return EXIT_SUCCESS;
}
