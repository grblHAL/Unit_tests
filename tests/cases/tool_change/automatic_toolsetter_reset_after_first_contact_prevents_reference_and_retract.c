#include "support/toolsetter_hook_host.h"

static unsigned completed_passes, contact_pulses;
static int32_t contact_position;
static void reset_after_setter_contact(void)
{
    CHECK(++completed_passes == 1 && sys.flags.probe_succeeded);
    contact_position = physical_position[Z_AXIS];
    contact_pulses = axis_pulses[Z_AXIS];
    CHECK(protocol_enqueue_realtime_command(CMD_RESET));
}

int main(void)
{
    prepare_fixture_probe_hook(ToolChange_SemiAutomatic);
    grbl.on_probe_completed = reset_after_setter_contact;
    run_automatic_toolsetter();
    CHECK(completed_passes == 1 && reset_calls == 1 && sys.abort);
    CHECK(!HOST_PARSER_FLAGS.tool_change);
    CHECK(!(sys.tlo_reference_set.mask & Z_AXIS_BIT));
    CHECK(physical_position[Z_AXIS] == contact_position);
    CHECK(axis_pulses[Z_AXIS] == contact_pulses);
    CHECK(setter_enable_calls > 0 && setter_disable_calls > 0);
    CHECK(hal.probe.get_state().probe_id == Probe_Default);
    CHECK(tool_stream_handler == original_enqueue);
    CHECK(hal.control.interrupt_callback == original_control);
    CHECK(!(sys.rt_exec_state & EXEC_CYCLE_START));
    CHECK(manual_tool_changed_calls == 0);
    return EXIT_SUCCESS;
}
