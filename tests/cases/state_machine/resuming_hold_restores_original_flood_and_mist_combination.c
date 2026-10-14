#include "support/hold_coolant_host.h"
int main(void)
{
    start_coolant_hold(true, true);
    toggle_hold_coolant(CMD_OVERRIDE_COOLANT_FLOOD_TOGGLE);
    CHECK(!held_coolant_output.flood && held_coolant_output.mist);
    int32_t stopped = physical_position[X_AXIS];
    resume_coolant_hold();
    CHECK(held_coolant_output.flood && held_coolant_output.mist);
    CHECK(gc_state.modal.coolant.flood && gc_state.modal.coolant.mist);
    CHECK(held_coolant_transition_position == stopped);
    return EXIT_SUCCESS;
}
