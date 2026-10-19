#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // M53 P0 - Disable feed hold override
    char block1[] = "M53P0";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(sys.override.control.feed_hold_disable == Off);

    // M53 P1 - Enable feed hold override
    char block2[] = "M53P1";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(sys.override.control.feed_hold_disable == On);

    // M56 P0 - Disable parking override (requires parking enable_override_control)
    char block3[] = "M56P0";
    CHECK(gc_execute_block(block3) == Status_GcodeUnsupportedCommand);

    // Enable parking override control and test M56
    settings.parking.flags.enable_override_control = true;
    char block4[] = "M56P0";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(sys.override.control.parking_disable == Off);

    // M56 P1 - Enable parking override
    char block5[] = "M56P1";
    CHECK(gc_execute_block(block5) == Status_OK);
    CHECK(sys.override.control.parking_disable == On);

    return EXIT_SUCCESS;
}