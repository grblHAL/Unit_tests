#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block0[] = "M48";
    CHECK(gc_execute_block(block0) == Status_OK);
    char block1[] = "M50P0";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == On);
    char block2[] = "M51P0";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 1);
    char block3[] = "M53P0";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(sys.override.control.feed_hold_disable == On);
    settings.parking.flags.enable_override_control = true;
    char block4[] = "M56P0";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(sys.override.control.parking_disable == On);

    return EXIT_SUCCESS;
}
