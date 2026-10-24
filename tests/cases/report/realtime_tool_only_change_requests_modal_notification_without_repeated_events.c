#include "support/report_host.h"
#include "state_machine.h"

static unsigned notifications, tool_changes;
static void tool_mode_changed(void) { notifications++; }
static void observe_tool_changed(tool_data_t *tool)
{
    CHECK(tool == gc_state.tool && tool->tool_id == 7);
    tool_changes++;
}

int main(void)
{
    prepare_report();
    state_set(STATE_IDLE);
    char mask[] = "512";
    CHECK(settings_store_setting(Setting_StatusReportMask, mask) == Status_OK);
    grbl.on_gcode_mode_changed = tool_mode_changed;
    grbl.on_tool_changed = observe_tool_changed;
    realtime_report();
    realtime_report();
    system_clear_exec_state_flag(EXEC_GCODE_REPORT);
    notifications = 0;
    engine_output[0] = 0;
    char select_tool[] = "M61Q7";
    CHECK(gc_execute_block(select_tool) == Status_OK);
    CHECK(gc_state.tool->tool_id == 7 && tool_changes == 1);
    realtime_report();
    CHECK(notifications == 1 && (sys.rt_exec_state & EXEC_GCODE_REPORT));
    report_gcode_modes(hal.stream.write);
    CHECK(strstr(engine_output, " T7 ") != NULL);
    system_clear_exec_state_flag(EXEC_GCODE_REPORT);
    realtime_report();
    CHECK(notifications == 1 && !(sys.rt_exec_state & EXEC_GCODE_REPORT));
    CHECK(plan_get_current_block() == NULL);
    CHECK(sys.position[X_AXIS] == 0 && sys.position[Y_AXIS] == 0 && sys.position[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
