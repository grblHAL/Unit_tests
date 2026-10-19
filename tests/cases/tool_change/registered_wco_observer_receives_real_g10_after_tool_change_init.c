#include "support/tool_wco_observer_host.h"
int main(void)
{
    prepare_tool_wco_observer();
    tool_wco_block("G10L2P1X4Y5Z6");
    CHECK(tool_wco_events == 1 && tool_wco_id == CoordinateSystem_G54);
    NEAR(tool_wco_data.coord.x, 4);
    NEAR(tool_wco_data.coord.y, 5);
    NEAR(tool_wco_data.coord.z, 6);
    CHECK(plan_get_current_block() == NULL);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
