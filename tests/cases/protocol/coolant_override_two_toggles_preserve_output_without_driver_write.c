#include "support/coolant_host.h"
#include "override.h"
#include "check.h"

int main(void)
{
    prepare_coolant(); hal.coolant_cap.flood = true;
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_COOLANT_FLOOD_TOGGLE));
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_COOLANT_FLOOD_TOGGLE));
    CHECK(protocol_exec_rt_system());
    CHECK(!gc_state.modal.coolant.flood); CHECK(coolant_calls == 0); CHECK(get_coolant_override() == 0);
    return EXIT_SUCCESS;
}
