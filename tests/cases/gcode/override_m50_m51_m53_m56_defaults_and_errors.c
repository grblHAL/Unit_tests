#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // M50 without P word - should use default P=1.0 (enable)
    char block1[] = "M50";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);

    // M51 without P word - should use default P=1.0 (enable)
    char block2[] = "M51";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    // M53 without P word - should use default P=1.0 (enable)
    char block3[] = "M53";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(sys.override.control.feed_hold_disable == On);

    // M56 without P word - requires parking override control enabled
    settings.parking.flags.enable_override_control = true;
    char block4[] = "M56";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(sys.override.control.parking_disable == On);

    // M50 with negative P - should fail
    char block5[] = "M50P-1";
    CHECK(gc_execute_block(block5) == Status_NegativeValue);

    // M51 with negative P - should fail
    char block6[] = "M51P-1";
    CHECK(gc_execute_block(block6) == Status_NegativeValue);

    // M53 with negative P - should fail
    char block7[] = "M53P-1";
    CHECK(gc_execute_block(block7) == Status_NegativeValue);

    // M56 with negative P - should fail
    char block8[] = "M56P-1";
    CHECK(gc_execute_block(block8) == Status_NegativeValue);

    return EXIT_SUCCESS;
}