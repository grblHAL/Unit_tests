#include "support/hold_coolant_host.h"
int main(void)
{
    start_coolant_hold(false, true);
    toggle_hold_coolant(CMD_OVERRIDE_COOLANT_MIST_TOGGLE);
    CHECK(held_coolant_output.flood && !held_coolant_output.mist);
    unsigned calls = held_coolant_calls;
    resume_coolant_hold();
    CHECK(held_coolant_output.flood && !held_coolant_output.mist);
    CHECK(gc_state.modal.coolant.flood && !gc_state.modal.coolant.mist);
    CHECK(held_coolant_calls == calls);
    return EXIT_SUCCESS;
}
