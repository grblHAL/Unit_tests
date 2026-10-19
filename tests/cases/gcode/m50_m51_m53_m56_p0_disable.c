#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // Enable overrides first
    char block0[] = "M48";
    CHECK(gc_execute_block(block0) == Status_OK);

    // M50 P0 - Disable feed override
    char block1[] = "M50P0";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == On);

    // M51 P0 - Disable spindle override
    char block2[] = "M51P0";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 1);

    // M53 P0 - Disable feed hold override
    char block3[] = "M53P0";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(sys.override.control.feed_hold_disable == Off);

    // M56 P0 - Disable parking override
    settings.parking.flags.enable_override_control = true;
    char block4[] = "M56P0";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(sys.override.control.parking_disable == Off);

    return EXIT_SUCCESS;
}