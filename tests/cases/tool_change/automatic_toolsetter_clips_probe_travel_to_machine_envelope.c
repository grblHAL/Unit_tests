#include "support/toolsetter_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_toolsetter_motion(ToolChange_SemiAutomatic);
    CHECK(probe_add(Probe_Default,0,IRQ_Mode_None,&toolsetter_contact_z,toolsetter_contact));
    sys.work_envelope.min.z=-4; run_automatic_toolsetter(); CHECK(!gc_state.tool_change);
    CHECK(sys.tlo_reference_set.mask & Z_AXIS_BIT); CHECK(sys.probe_position[Z_AXIS]>=-320);
    CHECK(sys.probe_position[Z_AXIS]<=-240); CHECK(physical_position[Z_AXIS]==-80); CHECK(sys.rt_exec_state & EXEC_CYCLE_START);
    return EXIT_SUCCESS;
}
