#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change_motion();
    coord_system_data_t g30 = {0};
    g30.coord.values[X_AXIS] = 4;
    g30.coord.values[Y_AXIS] = 5;
    g30.coord.values[Z_AXIS] = -0.5f;
    settings_write_coord_data(CoordinateSystem_G30, &g30);
    settings.flags.tool_change_at_g30 = true;
    sys.homed.mask = X_AXIS_BIT | Y_AXIS_BIT | Z_AXIS_BIT;
    start_manual_change();
    CHECK(sys.position[X_AXIS] == 320 && sys.position[Y_AXIS] == 400);
    CHECK(sys.position[Z_AXIS] == -40);
    CHECK(axis_pulses[Z_AXIS] == 120);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
