#include "support/toolsetter_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_toolsetter_motion(ToolChange_SemiAutomatic);
    CHECK(probe_add(Probe_Default,0,IRQ_Mode_None,&toolsetter_contact_z,toolsetter_contact)); run_automatic_toolsetter();
    CHECK(!HOST_PARSER_FLAGS.tool_change); CHECK(sys.tlo_reference_set.mask & Z_AXIS_BIT);
    CHECK(sys.tlo_reference[Z_AXIS]==sys.probe_position[Z_AXIS]); CHECK(sys.tlo_reference[Z_AXIS]<=-240); CHECK(sys.tlo_reference[Z_AXIS]>=-242);
    CHECK(physical_position[X_AXIS]==160); CHECK(physical_position[Y_AXIS]==240); CHECK(physical_position[Z_AXIS]==-80);
    CHECK(sys.rt_exec_state & EXEC_CYCLE_START); CHECK(plan_get_current_block()==NULL); CHECK(tool_stream_handler==original_enqueue);
    return EXIT_SUCCESS;
}
