#pragma once
#include "support/lathe_cycle_capture_host.h"
#include "report.h"

static inline void check_roughing_mode_report(const char *command, const char *prefix)
{
    prepare_lathe_capture();
    report_init_fns(); report_init();
    CHECK(css_block(command) == Status_OK);
    CHECK(lathe_cycle_calls == 1);
    engine_output[0] = '\0';
    report_gcode_modes(hal.stream.write);
    fprintf(stderr, "Expected modal prefix %s; observed %s", prefix, engine_output);
    CHECK(strncmp(engine_output, prefix, strlen(prefix)) == 0);
}
