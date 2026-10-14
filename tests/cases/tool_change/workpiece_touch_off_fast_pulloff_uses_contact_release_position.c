#include "support/workpiece_touch_off_host.h"
int main(void)
{
    start_workpiece_touch_off(true);
    CHECK(workpiece_touch_off() == Status_OK);
    check_workpiece_touch_off();
    CHECK(sys.probe_position[Z_AXIS] >= -240 && sys.probe_position[Z_AXIS] <= -238);
    return EXIT_SUCCESS;
}
