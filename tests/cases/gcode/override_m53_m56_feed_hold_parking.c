#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "M53P0";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(sys.override.control.feed_hold_disable == On);
    char block2[] = "M53P1";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(sys.override.control.feed_hold_disable == Off);
    char block3[] = "M56P0";
    CHECK(gc_execute_block(block3) == Status_GcodeUnsupportedCommand);
    settings.parking.flags.enable_override_control = true;
    char block4[] = "M56P0";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(sys.override.control.parking_disable == On);
    char block5[] = "M56P1";
    CHECK(gc_execute_block(block5) == Status_OK);
    CHECK(sys.override.control.parking_disable == Off);

    return EXIT_SUCCESS;
}
