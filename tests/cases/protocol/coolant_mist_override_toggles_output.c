#include "support/coolant_host.h"
#include "override.h"
#include "check.h"

int main(void)
{
    prepare_coolant(); hal.coolant_cap.mist = true;
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_COOLANT_MIST_TOGGLE));
    CHECK(protocol_exec_rt_system());
    CHECK(gc_state.modal.coolant.mist); CHECK(actual_coolant.mist); CHECK(coolant_calls == 1);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_COOLANT_MIST_TOGGLE));
    CHECK(protocol_exec_rt_system());
    CHECK(!gc_state.modal.coolant.mist); CHECK(!actual_coolant.mist); CHECK(coolant_calls == 2);
    return EXIT_SUCCESS;
}
