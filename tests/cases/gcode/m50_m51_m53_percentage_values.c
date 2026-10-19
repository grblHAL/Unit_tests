#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // M50 P25 - Set feed override to 25%
    char block1[] = "M50P25";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.feed_rate == 25);

    // M50 P150 - Set feed override to 150%
    char block2[] = "M50P150";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(sys.override.feed_rate == 150);

    // M51 P50 - Set spindle override to 50%
    char block3[] = "M51P50";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    // M51 P200 - Set spindle override to 200%
    char block4[] = "M51P200";
    CHECK(gc_execute_block(block4) == Status_OK);

    // M53 P0.5 - Set feed hold override (not really a percentage)
    // M53 only takes 0 or 1
    char block5[] = "M53P1";
    CHECK(gc_execute_block(block5) == Status_OK);
    CHECK(sys.override.control.feed_hold_disable == On);

    return EXIT_SUCCESS;
}