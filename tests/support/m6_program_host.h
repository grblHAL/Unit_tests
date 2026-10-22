#pragma once
#include "support/tool_offset_host.h"
#include "protocol.h"
#include "state_machine.h"
#include "report.h"
#include <string.h>
static unsigned m6_change_calls, m6_select_calls, m6_selected_calls, m6_changed_calls;
static status_code_t m6_driver_status = Status_OK;
static atc_status_t m6_atc_state = ATC_Online;
static bool m6_wait_for_ack, m6_next_selection, m6_expect_named_message;
static tool_data_t *m6_selected_tool, *m6_changed_tool, *m6_driver_selected_tool;
static atc_status_t m6_get_atc_state(void) { return m6_atc_state; }
static control_signals_t m6_control_state(void) { return (control_signals_t){0}; }
static bool m6_connected(void) { return true; }
static void m6_driver_select(tool_data_t *tool, bool next)
{
    CHECK(tool != NULL);
    m6_select_calls++;
    m6_driver_selected_tool = tool;
    m6_next_selection = next;
}
static void m6_selected(tool_data_t *tool) { CHECK(tool != NULL); m6_selected_calls++; m6_selected_tool = tool; }
static void m6_changed(tool_data_t *tool) { CHECK(tool != NULL); m6_changed_calls++; m6_changed_tool = tool; }
static status_code_t m6_driver_change(parser_state_t *parser)
{
    CHECK(parser == &gc_state);
    m6_change_calls++;
    if(m6_expect_named_message) CHECK(strstr(engine_output, "[MSG:End mill]" ASCII_EOL) != NULL);
    if(m6_wait_for_ack && m6_driver_status == Status_OK) {
        HOST_PARSER_FLAGS.tool_change = true;
        state_set(STATE_TOOL_CHANGE);
    }
    return m6_driver_status;
}
static inline void prepare_m6_program(void)
{
    prepare_offset_tool();
    hal.driver_cap.atc = true;
    hal.tool.atc_get_state = m6_get_atc_state;
    hal.tool.select = m6_driver_select;
    hal.tool.change = m6_driver_change;
    hal.control.get_state = m6_control_state;
    hal.stream.is_connected = m6_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    grbl.on_tool_selected = m6_selected;
    grbl.on_tool_changed = m6_changed;
    settings.status_report.sync_on_wco_change = false;
    report_init_fns();
    report_init();
    state_set(STATE_IDLE);
}
static inline status_code_t m6_block(const char *text)
{
    char block[96];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    return gc_execute_block(block);
}
