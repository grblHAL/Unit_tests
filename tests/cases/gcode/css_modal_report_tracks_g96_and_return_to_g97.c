#include "support/css_host.h"
#include "report.h"
int main(void)
{
    prepare_css_parser(true);
    report_init_fns();
    report_init();
    CHECK(css_block("G96S100D2500") == Status_OK);
    engine_output[0] = 0;
    report_gcode_modes(hal.stream.write);
    CHECK(strstr(engine_output, " G96 ") != NULL);
    CHECK(strstr(engine_output, " G97 ") == NULL);
    CHECK(css_block("G97S1800") == Status_OK);
    engine_output[0] = 0;
    report_gcode_modes(hal.stream.write);
    CHECK(strstr(engine_output, " G97 ") != NULL);
    CHECK(strstr(engine_output, " G96 ") == NULL);
    NEAR(gc_spindle_get(0)->rpm, 1800);
    return EXIT_SUCCESS;
}
