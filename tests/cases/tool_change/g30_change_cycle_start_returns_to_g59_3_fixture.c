#include "support/toolsetter_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_toolsetter_motion(ToolChange_Manual_G59_3); settings.flags.tool_change_at_g30=true;
    coord_system_data_t change={.coord={.x=4,.y=5,.z=-3}}; settings_write_coord_data(CoordinateSystem_G30,&change);
    start_manual_change(); CHECK(physical_position[X_AXIS]==320); CHECK(physical_position[Y_AXIS]==400); CHECK(physical_position[Z_AXIS]==-240);
    grbl.on_toolchange_ack(); CHECK(tool_stream_handler(CMD_CYCLE_START)); engine_execute_tasks(STATE_TOOL_CHANGE);
    CHECK(gc_state.tool_change); CHECK(physical_position[X_AXIS]==80); CHECK(physical_position[Y_AXIS]==80); CHECK(physical_position[Z_AXIS]==-160);
    CHECK(toolsetter_xy_pulses>0); CHECK(plan_get_current_block()==NULL);
    return EXIT_SUCCESS;
}
