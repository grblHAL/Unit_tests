#include "support/parking_host.h"
#include "check.h"

int main(void)
{
    start_parking_move();
    park_until_retracted();
    CHECK(state_get() == STATE_SAFETY_DOOR);
    CHECK(sys.position[Z_AXIS] == -160);
    CHECK(physical_position[Z_AXIS] == -160);
    CHECK(axis_pulses[Z_AXIS] == 640);
    CHECK(sys.position[X_AXIS] > 0 && sys.position[X_AXIS] < 1600);
    CHECK(plan_get_current_block() != NULL);
    CHECK(state_get_substate() == Parking_DoorAjar);
    return EXIT_SUCCESS;
}
