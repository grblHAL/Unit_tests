#include "support/incoming_gcode_host.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "M48";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.control.spindle_rpm_disable == 0);
    sys.override.feed_rate = 50;
    sys.override.rapid_rate = 50;
    spindle_set_override(spindle_get(0), 75);
    CHECK(spindle_get(0)->param->override_pct == 75);
    char block2[] = "M70";
    CHECK(gc_execute_block(block2) == Status_OK);
    char block3[] = "M49";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == On);
    CHECK(sys.override.control.spindle_rpm_disable == 1);
    sys.override.feed_rate = 100;
    sys.override.rapid_rate = 100;
    spindle_set_override(spindle_get(0), 100);
    char block4[] = "M72";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.control.spindle_rpm_disable == 0);
    CHECK(sys.override.feed_rate == 50);
    CHECK(sys.override.rapid_rate == 50);
    CHECK(spindle_get(0)->param->override_pct == 75);

    return EXIT_SUCCESS;
}
