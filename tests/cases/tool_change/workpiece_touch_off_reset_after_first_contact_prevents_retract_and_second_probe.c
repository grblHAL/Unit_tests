#include "support/workpiece_touch_off_host.h"

static on_probe_completed_ptr touch_off_completed;
static unsigned completed_passes, contact_pulses;
static int32_t contact_position;
static void reset_after_contact(void)
{
    CHECK(++completed_passes == 1 && sys.flags.probe_succeeded);
    touch_off_completed();
    contact_position = physical_position[Z_AXIS];
    contact_pulses = axis_pulses[Z_AXIS];
    CHECK(protocol_enqueue_realtime_command(CMD_RESET));
}

int main(void)
{
    start_workpiece_touch_off(false);
    touch_off_completed = grbl.on_probe_completed;
    CHECK(touch_off_completed != NULL);
    grbl.on_probe_completed = reset_after_contact;
    CHECK(workpiece_touch_off() == Status_GCodeToolError);
    CHECK(completed_passes == 1 && reset_calls == 1 && sys.abort);
    CHECK(!HOST_PARSER_FLAGS.tool_change);
    CHECK(physical_position[Z_AXIS] == contact_position);
    CHECK(axis_pulses[Z_AXIS] == contact_pulses);
    CHECK(physical_position[X_AXIS] == 160 && physical_position[Y_AXIS] == 240);
    CHECK(tool_stream_handler == original_enqueue);
    CHECK(hal.control.interrupt_callback == original_control);
    CHECK(!(sys.rt_exec_state & EXEC_CYCLE_START));
    CHECK(manual_tool_changed_calls == 0);
    grbl.on_probe_completed = touch_off_completed;
    return EXIT_SUCCESS;
}
