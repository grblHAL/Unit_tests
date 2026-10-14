#include "support/parking_accessory_host.h"
int main(void)
{
    start_powered_parking_move(false);
    park_until_retracted();
    CHECK(!parking_spindle_state.on && !parking_coolant.flood);
    CHECK(parking_spindle_off_z == -640 && parking_coolant_off_z == -640);
    CHECK(physical_position[Z_AXIS] == -160);
    CHECK(gc_spindle_get(0)->state.on && gc_state.modal.coolant.flood);
    CHECK(plan_get_current_block() != NULL);
    return EXIT_SUCCESS;
}
