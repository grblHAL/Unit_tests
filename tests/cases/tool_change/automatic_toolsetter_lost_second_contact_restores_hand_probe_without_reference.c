#include "support/toolsetter_hook_host.h"

static unsigned completed_passes;
static void remove_setter_after_first_contact(void)
{
    completed_passes++;
    if(completed_passes == 1) {
        CHECK(sys.flags.probe_succeeded);
        setter_hook_contact_z = -16000;
    }
}

int main(void)
{
    prepare_fixture_probe_hook(ToolChange_SemiAutomatic);
    grbl.on_probe_completed = remove_setter_after_first_contact;
    run_automatic_toolsetter();
    CHECK(completed_passes == 2);
    CHECK(!sys.flags.probe_succeeded && !HOST_PARSER_FLAGS.tool_change);
    CHECK(!(sys.tlo_reference_set.mask & Z_AXIS_BIT));
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_Cancel);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 0);
    CHECK(sys.alarm == Alarm_ProbeFailContact);
    CHECK(setter_enable_calls > 0 && setter_disable_calls > 0);
    CHECK(hal.probe.get_state().probe_id == Probe_Default);
    CHECK(tool_stream_handler == original_enqueue);
    CHECK(hal.control.interrupt_callback == original_control);
    CHECK(!(sys.rt_exec_state & EXEC_CYCLE_START));
    CHECK(plan_get_current_block() == NULL);
    CHECK(grbl.on_probe_completed == remove_setter_after_first_contact);
    return EXIT_SUCCESS;
}
