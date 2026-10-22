#include "support/toolsetter_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_toolsetter_motion(ToolChange_SemiAutomatic);
    CHECK(probe_add(Probe_Default,0,IRQ_Mode_None,&toolsetter_contact_z,toolsetter_contact));
    toolsetter_contact_z=-16000; run_automatic_toolsetter(); CHECK(!HOST_PARSER_FLAGS.tool_change);
    CHECK(!(sys.tlo_reference_set.mask & Z_AXIS_BIT)); CHECK(!sys.flags.probe_succeeded); CHECK(!(sys.rt_exec_state & EXEC_CYCLE_START));
    CHECK(tool_stream_handler==original_enqueue); CHECK(hal.control.interrupt_callback==original_control); CHECK(sys.alarm==Alarm_ProbeFailContact);
    CHECK(plan_get_current_block()==NULL);
    return EXIT_SUCCESS;
}
