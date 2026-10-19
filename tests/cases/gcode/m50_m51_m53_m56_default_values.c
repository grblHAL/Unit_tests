#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // M50 without P - Default P=1.0 (enable feed override)
    char block1[] = "M50";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);

    // M51 without P - Default P=1.0 (enable spindle override)
    char block2[] = "M51";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    // M53 without P - Default P=1.0 (enable feed hold override)
    char block3[] = "M53";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(sys.override.control.feed_hold_disable == On);

    // M56 without P - Default P=1.0 (enable parking override)
    settings.parking.flags.enable_override_control = true;
    char block4[] = "M56";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(sys.override.control.parking_disable == On);

    return EXIT_SUCCESS;
}