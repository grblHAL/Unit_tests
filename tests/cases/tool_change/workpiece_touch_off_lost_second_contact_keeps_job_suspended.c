#include "support/workpiece_touch_off_host.h"

static on_probe_completed_ptr touch_off_completed;
static unsigned completed_passes;
static void remove_plate_after_first_contact(void)
{
    completed_passes++;
    if(completed_passes == 1) {
        CHECK(sys.flags.probe_succeeded);
        toolsetter_contact_z = -16000;
    }
    touch_off_completed();
}

int main(void)
{
    start_workpiece_touch_off(false);
    touch_off_completed = grbl.on_probe_completed;
    CHECK(touch_off_completed != NULL);
    grbl.on_probe_completed = remove_plate_after_first_contact;
    CHECK(workpiece_touch_off() == Status_GCodeToolError);
    CHECK(completed_passes == 2);
    CHECK(!sys.flags.probe_succeeded);
    CHECK(HOST_PARSER_FLAGS.tool_change);
    CHECK(!(sys.rt_exec_state & EXEC_CYCLE_START));
    CHECK(tool_stream_handler != original_enqueue);
    CHECK(plan_get_current_block() == NULL);
    CHECK(physical_position[X_AXIS] == 160 && physical_position[Y_AXIS] == 240);
    CHECK(strstr(engine_output, "Probe failed, try again.") != NULL);
    grbl.on_probe_completed = touch_off_completed;
    return EXIT_SUCCESS;
}
