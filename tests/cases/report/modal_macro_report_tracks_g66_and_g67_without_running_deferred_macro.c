#include "support/report_host.h"
#include "support/macro_parser_host.h"
int main(void)
{
    prepare_report();
    grbl.on_macro_execute = capture_macro;
    CHECK(macro_block("G66P100X12") == Status_OK);
    report_gcode_modes(hal.stream.write);
    CHECK(strstr(engine_output, " G66 G90 ") != NULL);
    CHECK(macro_calls == 0);
    CHECK(macro_block("G67") == Status_OK);
    engine_output[0] = 0;
    report_gcode_modes(hal.stream.write);
    CHECK(strstr(engine_output, " G66 ") == NULL);
    CHECK(macro_calls == 0 && gc_state.g66_args == NULL);
    return EXIT_SUCCESS;
}
