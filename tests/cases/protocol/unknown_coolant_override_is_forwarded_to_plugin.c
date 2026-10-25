#include "support/coolant_host.h"
#include "override.h"
#include "check.h"
static unsigned unknown_calls; static uint8_t unknown_value;
static void record_unknown(uint8_t value) { unknown_calls++; unknown_value = value; }
int main(void)
{
    prepare_coolant();
    hal.coolant_cap.flood = true;
    CHECK(grbl.on_unknown_accessory_override == NULL);
    enqueue_coolant_override(0xEE); CHECK(protocol_exec_rt_system());
    CHECK(coolant_calls == 0 && get_coolant_override() == 0 && unknown_calls == 0);
    grbl.on_unknown_accessory_override = record_unknown;
    enqueue_coolant_override(0xEE); CHECK(protocol_exec_rt_system());
    CHECK(unknown_calls == 1); CHECK(unknown_value == 0xEE); CHECK(coolant_calls == 0);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_COOLANT_FLOOD_TOGGLE));
    CHECK(protocol_exec_rt_system());
    CHECK(coolant_calls == 1 && actual_coolant.flood && gc_state.modal.coolant.flood);
    CHECK(unknown_calls == 1 && get_coolant_override() == 0);
    return EXIT_SUCCESS;
}
