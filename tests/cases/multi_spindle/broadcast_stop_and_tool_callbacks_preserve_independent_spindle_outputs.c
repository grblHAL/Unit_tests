#include "support/multi_spindle_modal_host.h"

static unsigned selected_calls, changed_calls, driver_changes;
static tool_id_t expected_tool = 1;
static void select_and_stop(tool_data_t *tool)
{
    CHECK(tool->tool_id == expected_tool);
    selected_calls++;
    gc_spindle_off();
}
static void tool_changed(tool_data_t *tool)
{
    CHECK(tool->tool_id == expected_tool);
    changed_calls++;
}
static atc_status_t online_changer(void) { return ATC_Online; }
static status_code_t change_tool(parser_state_t *parser)
{
    CHECK(parser == &gc_state && parser->tool_pending == expected_tool);
    CHECK(!actual_spindle_states[0].on && !actual_spindle_states[1].on);
    driver_changes++;
    return Status_OK;
}
int main(void)
{
    prepare_multi_spindle_modal_program();
    hal.driver_cap.atc = true;
    hal.tool.atc_get_state = online_changer;
    hal.tool.change = change_tool;
    start_two_modal_spindles();
    grbl.on_tool_selected = select_and_stop;
    grbl.on_tool_changed = tool_changed;
    CHECK(spindle_program_block("M5$-1M61Q1") == Status_OK);
    CHECK(selected_calls == 1 && changed_calls == 1);
    CHECK(gc_state.tool->tool_id == 1 && gc_state.tool_pending == 1);
    for(unsigned slot = 0; slot < 2; slot++) {
        CHECK(!actual_spindle_states[slot].on);
        CHECK(!gc_spindle_get(slot)->state.on);
        NEAR(actual_spindle_rpm[slot], 0);
    }
    CHECK(spindle_program_block("M3S4000$0") == Status_OK);
    CHECK(spindle_program_block("M4S6000$1") == Status_OK);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
    CHECK(actual_spindle_states[1].on && actual_spindle_states[1].ccw);
    NEAR(actual_spindle_rpm[0], 4000);
    NEAR(actual_spindle_rpm[1], 6000);
    CHECK(driver_changes == 0);
    expected_tool = 2;
    CHECK(spindle_program_block("M5$-1T2M6") == Status_OK);
    CHECK(driver_changes == 1 && selected_calls == 2 && changed_calls == 2);
    CHECK(gc_state.tool->tool_id == 2 && gc_state.tool_pending == 2);
    for(unsigned slot = 0; slot < 2; slot++) {
        CHECK(!actual_spindle_states[slot].on && !gc_spindle_get(slot)->state.on);
        NEAR(actual_spindle_rpm[slot], 0);
    }
    CHECK(spindle_program_block("M3S5000$1") == Status_OK);
    CHECK(!actual_spindle_states[0].on && actual_spindle_states[1].on);
    NEAR(actual_spindle_rpm[1], 5000);
    CHECK(selected_calls == 2 && changed_calls == 2 && spindle_output_calls[2] == 0);
    CHECK(plan_get_current_block() == NULL && state_get() == STATE_IDLE);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
