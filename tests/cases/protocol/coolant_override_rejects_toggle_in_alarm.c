#include "support/coolant_host.h"
#include "override.h"
#include "check.h"

int main(void)
{
    prepare_coolant(); hal.coolant_cap.flood = true; state_set(STATE_ALARM);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_COOLANT_FLOOD_TOGGLE));
    CHECK(protocol_exec_rt_system());
    CHECK(!gc_state.modal.coolant.flood); CHECK(!actual_coolant.flood); CHECK(coolant_calls == 0);
    return EXIT_SUCCESS;
}
