#include "support/toolsetter_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_toolsetter_motion(ToolChange_SemiAutomatic);
    CHECK(probe_add(Probe_Default,0,IRQ_Mode_None,&toolsetter_contact_z,toolsetter_contact));
    sys.tlo_reference_set.mask=Z_AXIS_BIT; sys.tlo_reference[Z_AXIS]=-320; run_automatic_toolsetter();
    CHECK(!gc_state.tool_change); CHECK(sys.tlo_reference[Z_AXIS]==-320); CHECK(gc_state.modal.tool_offset_mode==ToolLengthOffset_EnableDynamic);
    CHECK(fabsf(gc_state.modal.tool_length_offset[Z_AXIS]-1.0f)<0.025f);
    NEAR((float)physical_position[Z_AXIS]/settings.axis[Z_AXIS].steps_per_mm-gc_state.modal.tool_length_offset[Z_AXIS],-1);
    CHECK(physical_position[X_AXIS]==160); CHECK(physical_position[Y_AXIS]==240); CHECK(sys.rt_exec_state & EXEC_CYCLE_START);
    return EXIT_SUCCESS;
}
