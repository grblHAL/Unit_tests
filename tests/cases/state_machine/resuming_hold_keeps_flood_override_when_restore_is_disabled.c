#include "support/hold_coolant_host.h"
int main(void)
{
    start_coolant_hold(false, false);
    toggle_hold_coolant(CMD_OVERRIDE_COOLANT_FLOOD_TOGGLE);
    CHECK(!held_coolant_output.flood);
    unsigned calls = held_coolant_calls;
    resume_coolant_hold();
    CHECK(!held_coolant_output.flood && !gc_state.modal.coolant.flood);
    CHECK(held_coolant_calls == calls);
    return EXIT_SUCCESS;
}
