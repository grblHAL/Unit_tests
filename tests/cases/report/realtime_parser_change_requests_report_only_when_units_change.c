#include "support/report_host.h"
#include "protocol.h"
#include "check.h"
static unsigned mode_change_calls;
static void mode_changed(void) { mode_change_calls++; }
int main(void)
{
    prepare_report();
    settings.status_report.parser_state = true;
    grbl.on_gcode_mode_changed = mode_changed;
    char inches[] = "G20";
    CHECK(gc_execute_block(inches) == Status_OK);
    realtime_report();
    CHECK(sys.rt_exec_state & EXEC_GCODE_REPORT);
    CHECK(mode_change_calls == 1);
    system_clear_exec_state_flag(EXEC_GCODE_REPORT);
    engine_output[0] = '\0';
    realtime_report();
    CHECK(!(sys.rt_exec_state & EXEC_GCODE_REPORT));
    CHECK(mode_change_calls == 1);
    char metric[] = "G21";
    CHECK(gc_execute_block(metric) == Status_OK);
    realtime_report();
    CHECK(sys.rt_exec_state & EXEC_GCODE_REPORT);
    CHECK(mode_change_calls == 2);
    return EXIT_SUCCESS;
}
