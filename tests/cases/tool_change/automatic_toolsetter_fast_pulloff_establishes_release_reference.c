#include "support/toolsetter_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_toolsetter_motion(ToolChange_SemiAutomatic);
    CHECK(probe_add(Probe_Default,0,IRQ_Mode_None,&toolsetter_contact_z,toolsetter_contact));
    settings.flags.tool_change_fast_pulloff=true; run_automatic_toolsetter(); CHECK(!gc_state.tool_change);
    CHECK(sys.tlo_reference_set.mask & Z_AXIS_BIT); CHECK(sys.tlo_reference[Z_AXIS]==sys.probe_position[Z_AXIS]);
    CHECK(sys.tlo_reference[Z_AXIS]>=-240); CHECK(sys.tlo_reference[Z_AXIS]<=-238);
    CHECK(physical_position[Z_AXIS]==-80); CHECK(physical_position[X_AXIS]==160); CHECK(physical_position[Y_AXIS]==240);
    CHECK(sys.rt_exec_state & EXEC_CYCLE_START);
    return EXIT_SUCCESS;
}
