#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // M50 P0 - Disable feed rate override
    char block1[] = "M50P0";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == On);

    // M50 P50 - Enable feed rate override at 50%
    char block2[] = "M50P50";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);

    // M51 P0 - Disable spindle speed override
    char block3[] = "M51P0";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 1);

    // M51 P75 - Enable spindle speed override at 75%
    char block4[] = "M51P75";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    return EXIT_SUCCESS;
}