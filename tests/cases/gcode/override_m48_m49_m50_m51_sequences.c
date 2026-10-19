#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    CHECK(incoming_block("M48") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    CHECK(incoming_block("M49") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == On);
    CHECK(sys.override.control.spindle_rpm_disable == 1);

    CHECK(incoming_block("M48") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(incoming_block("M50P0") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == On);

    CHECK(incoming_block("M50P50") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.feed_rate == 100);
    CHECK(incoming_block("M51P0") == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 1);

    CHECK(incoming_block("M51P50") == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    return EXIT_SUCCESS;
}
