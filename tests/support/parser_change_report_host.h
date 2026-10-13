#pragma once
#include "support/report_host.h"
#include "support/named_parameter_host.h"
static unsigned parser_change_calls;
static void parser_changed(void) { parser_change_calls++; }
static void prepare_parser_change_report(void)
{
    prepare_report();
    settings.status_report.parser_state = true;
    grbl.on_gcode_mode_changed = parser_changed;
    realtime_report();
    realtime_report();
    system_clear_exec_state_flag(EXEC_GCODE_REPORT);
    parser_change_calls = 0;
    engine_output[0] = 0;
}
static inline void expect_parser_change_report(void)
{
    unsigned before = parser_change_calls;
    realtime_report();
    CHECK(sys.rt_exec_state & EXEC_GCODE_REPORT);
    CHECK(parser_change_calls == before + 1);
    system_clear_exec_state_flag(EXEC_GCODE_REPORT);
    engine_output[0] = 0;
}
