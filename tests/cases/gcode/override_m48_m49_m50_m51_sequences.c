#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // M48 M49 sequence
    CHECK(gc_execute_block("M48") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    CHECK(gc_execute_block("M49") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == On);
    CHECK(sys.override.control.spindle_rpm_disable == 1);

    CHECK(gc_execute_block("M48") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);

    // M50 P0 M50 P100
    CHECK(gc_execute_block("M50P0") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == On);

    CHECK(gc_execute_block("M50P50") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.feed_rate == 50);

    // M51 P0 M51 P75
    CHECK(gc_execute_block("M51P0") == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 1);

    CHECK(gc_execute_block("M51P50") == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    return EXIT_SUCCESS;
}