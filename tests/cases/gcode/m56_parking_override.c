#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // M56 P0 - Disable parking override (requires parking enable_override_control)
    settings.parking.flags.enable_override_control = true;
    char block1[] = "M56P0";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(sys.override.control.parking_disable == Off);

    // M56 P1 - Enable parking override
    char block2[] = "M56P1";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(sys.override.control.parking_disable == On);

    // M56 without P - Default P=1
    char block3[] = "M56";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(sys.override.control.parking_disable == On);

    // M56 without parking enable_override_control
    settings.parking.flags.enable_override_control = false;
    char block4[] = "M56P0";
    CHECK(gc_execute_block(block4) == Status_GcodeUnsupportedCommand);

    return EXIT_SUCCESS;
}