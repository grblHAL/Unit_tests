#include "support/coolant_host.h"
#include "override.h"
static unsigned notifications;
static void coolant_changed(override_changed_t changed)
{
    CHECK(changed == OverrideChanged_CoolantState);
    CHECK(gc_state.modal.coolant.flood && gc_state.modal.coolant.mist);
    CHECK(actual_coolant.flood && actual_coolant.mist);
    CHECK(coolant_calls == 1);
    notifications++;
}
int main(void)
{
    prepare_coolant();
    hal.coolant_cap.flood = hal.coolant_cap.mist = true;
    grbl.on_override_changed = coolant_changed;
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_COOLANT_FLOOD_TOGGLE));
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_COOLANT_MIST_TOGGLE));
    CHECK(protocol_exec_rt_system());
    CHECK(notifications == 1 && coolant_calls == 1);
    return EXIT_SUCCESS;
}
