#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    settings.parking.flags.enable_override_control = true;
    char block1[] = "M56P0";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(sys.override.control.parking_disable == On);
    char block2[] = "M56P1";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(sys.override.control.parking_disable == Off);
    char block3[] = "M56";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(sys.override.control.parking_disable == Off);
    settings.parking.flags.enable_override_control = false;
    char block4[] = "M56P0";
    CHECK(gc_execute_block(block4) == Status_GcodeUnsupportedCommand);

    return EXIT_SUCCESS;
}
