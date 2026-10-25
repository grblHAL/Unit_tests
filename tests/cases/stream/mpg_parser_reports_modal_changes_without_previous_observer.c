#include "support/mpg_stream_host.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(grbl.on_gcode_mode_changed == NULL);
    /* This board has no plugin observing pendant registration. */
    grbl.on_mpg_registered = NULL;
    char report_mask[] = "512";
    CHECK(settings_store_setting(Setting_StatusReportMask, report_mask) == Status_OK);
    CHECK(settings.status_report.parser_state);
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    CHECK(registered_calls == 0 && grbl.on_gcode_mode_changed != NULL);
    pendant_output[0] = 0;
    char inches[] = "G20";
    CHECK(gc_execute_block(inches) == Status_OK);
    realtime_report();
    CHECK(strstr(pendant_output, "[GC:G0 G54 G17 G20 G90") != NULL);
    CHECK(sys.rt_exec_state & EXEC_GCODE_REPORT);
    system_clear_exec_state_flag(EXEC_GCODE_REPORT);
    pendant_output[0] = 0;
    realtime_report();
    CHECK(pendant_output[0] == 0 && !(sys.rt_exec_state & EXEC_GCODE_REPORT));
    char metric[] = "G21";
    CHECK(gc_execute_block(metric) == Status_OK);
    realtime_report();
    CHECK(strstr(pendant_output, "[GC:G0 G54 G17 G21 G90") != NULL);
    return EXIT_SUCCESS;
}
