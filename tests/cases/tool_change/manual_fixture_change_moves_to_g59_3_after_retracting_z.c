#include "support/toolsetter_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_toolsetter_motion(ToolChange_Manual_G59_3); start_manual_change();
    CHECK(gc_state.tool_change); CHECK(state_get()==STATE_TOOL_CHANGE);
    CHECK(physical_position[X_AXIS]==80); CHECK(physical_position[Y_AXIS]==80); CHECK(physical_position[Z_AXIS]==-160);
    CHECK(toolsetter_xy_pulses>0); CHECK(plan_get_current_block()==NULL);
    NEAR(gc_state.position[X_AXIS],1); NEAR(gc_state.position[Y_AXIS],1); NEAR(gc_state.position[Z_AXIS],-2);
    return EXIT_SUCCESS;
}
