#include "support/workpiece_touch_off_host.h"
int main(void)
{
    prepare_toolsetter_motion(ToolChange_Manual);
    coord_system_data_t g30 = {.coord = {.x = 4, .y = 5, .z = -0.5f}};
    settings_write_coord_data(CoordinateSystem_G30, &g30);
    settings.flags.tool_change_at_g30 = true;
    start_manual_change();
    grbl.on_toolchange_ack();
    unsigned before[N_AXIS];
    memcpy(before, axis_pulses, sizeof(before));
    CHECK(workpiece_touch_off() == Status_OK);
    CHECK(memcmp(before, axis_pulses, sizeof(before)) == 0);
    CHECK(physical_position[X_AXIS] == 320 && physical_position[Y_AXIS] == 400);
    CHECK(physical_position[Z_AXIS] == -40);
    CHECK(gc_state.tool_change && !sys.flags.probe_succeeded);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
