#include "support/parking_host.h"
#include "support/report_host.h"
int main(void)
{
    start_parking_move(); park_until_retracted();
    report_init();
    hal.stream.is_connected = connected;
    CHECK(state_get() == STATE_SAFETY_DOOR && sys.parking_state == Parking_DoorAjar);
    engine_output[0] = '\0'; realtime_report();
    CHECK(strncmp(engine_output, "<Door:1|", 8) == 0);
    CHECK(physical_position[Z_AXIS] == -160 && sys.position[Z_AXIS] == -160);
    CHECK(plan_get_current_block() != NULL);
    return EXIT_SUCCESS;
}
