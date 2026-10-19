#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    // M48 - Enable feed and speed override
    char block1[] = "M48";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    // M49 - Disable feed and speed override
    char block2[] = "M49";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == On);
    CHECK(sys.override.control.spindle_rpm_disable == 1);

    // M48 again - Re-enable
    char block3[] = "M48";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    return EXIT_SUCCESS;
}