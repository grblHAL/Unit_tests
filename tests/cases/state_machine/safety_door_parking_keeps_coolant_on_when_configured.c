#include "support/parking_accessory_host.h"
int main(void)
{
    start_powered_parking_move(true);
    park_until_retracted();
    CHECK(!parking_spindle_state.on && parking_coolant.flood);
    CHECK(parking_coolant_off_calls == 0);
    CHECK(physical_position[Z_AXIS] == -160);
    return EXIT_SUCCESS;
}
