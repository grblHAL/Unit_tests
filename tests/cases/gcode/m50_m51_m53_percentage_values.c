#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "M50P25";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.feed_rate == 100);
    char block2[] = "M50P150";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(sys.override.feed_rate == 100);
    char block3[] = "M51P50";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 0);
    char block4[] = "M51P200";
    CHECK(gc_execute_block(block4) == Status_OK);
    char block5[] = "M53P1";
    CHECK(gc_execute_block(block5) == Status_OK);
    CHECK(sys.override.control.feed_hold_disable == Off);

    return EXIT_SUCCESS;
}
