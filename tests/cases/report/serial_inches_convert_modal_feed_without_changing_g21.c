#include "support/report_host.h"

int main(void)
{
    prepare_report();
    settings.flags.report_inches = true;
    report_init();
    gc_state.feed_rate = 1524;
    report_gcode_modes(hal.stream.write);
    CHECK(strstr(engine_output, " G21 ") != NULL);
    CHECK(strstr(engine_output, " F60]") != NULL);
    CHECK(!gc_state.modal.units_imperial);
    NEAR(gc_state.feed_rate, 1524);
    return EXIT_SUCCESS;
}
