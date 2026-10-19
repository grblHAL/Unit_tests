#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.control.spindle_rpm_disable == 0);
    char block1[] = "M48";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.control.spindle_rpm_disable == 0);
    char block2[] = "M49";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == On);
    CHECK(sys.override.control.spindle_rpm_disable == 1);
    char block3[] = "M48";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    return EXIT_SUCCESS;
}
