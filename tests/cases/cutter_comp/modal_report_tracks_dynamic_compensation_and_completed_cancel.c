#include "support/cutter_capture_host.h"
#include "report.h"
int main(void)
{
    prepare_cutter_capture();
    CHECK(cutter_block("G41.1D6") == Status_OK);
    engine_output[0] = 0;
    report_gcode_modes(hal.stream.write);
    CHECK(strstr(engine_output, " G41.1 ") != NULL);
    CHECK(cutter_enable_calls == 1 && cutter_received.dynamic);
    CHECK(cutter_block("G40") == Status_OK);
    CHECK(cutter_block("G1X10F100") == Status_OK);
    engine_output[0] = 0;
    report_gcode_modes(hal.stream.write);
    CHECK(strstr(engine_output, " G40 ") != NULL);
    CHECK(strstr(engine_output, " G41.1 ") == NULL);
    return EXIT_SUCCESS;
}
