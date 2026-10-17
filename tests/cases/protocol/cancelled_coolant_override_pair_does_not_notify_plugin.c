#include "support/coolant_host.h"
#include "override.h"
static unsigned notifications;
static void coolant_changed(override_changed_t changed)
{
    (void)changed;
    notifications++;
}
int main(void)
{
    prepare_coolant();
    hal.coolant_cap.flood = true;
    grbl.on_override_changed = coolant_changed;
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_COOLANT_FLOOD_TOGGLE));
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_COOLANT_FLOOD_TOGGLE));
    CHECK(protocol_exec_rt_system());
    CHECK(notifications == 0 && coolant_calls == 0);
    CHECK(!gc_state.modal.coolant.flood && !actual_coolant.flood);
    return EXIT_SUCCESS;
}
