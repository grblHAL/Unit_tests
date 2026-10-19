#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "M50P0";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == On);
    char block2[] = "M50P50";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    char block3[] = "M51P0";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 1);
    char block4[] = "M51P75";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    return EXIT_SUCCESS;
}
