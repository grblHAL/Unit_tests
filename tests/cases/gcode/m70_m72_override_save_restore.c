#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // Set overrides
    char block1[] = "M48";
    CHECK(gc_execute_block(block1) == Status_OK);

    sys.override.feed_rate = 75;
    sys.override.rapid_rate = 75;
    spindle_set_override(spindle_get(0), 80);
    CHECK(sys.override.feed_rate == 75);
    CHECK(spindle_get(0)->param->state.override_percentage == 80);

    // M70 - Save modal state
    char block2[] = "M70";
    CHECK(gc_execute_block(block2) == Status_OK);

    // Change overrides
    char block3[] = "M49";
    CHECK(gc_execute_block(block3) == Status_OK);
    sys.override.feed_rate = 100;
    sys.override.rapid_rate = 100;
    spindle_set_override(spindle_get(0), 100);

    // M72 - Restore modal state
    char block4[] = "M72";
    CHECK(gc_execute_block(block4) == Status_OK);

    // Overrides should be restored
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.feed_rate == 75);
    CHECK(sys.override.rapid_rate == 75);
    CHECK(spindle_get(0)->param->state.override_percentage == 80);

    return EXIT_SUCCESS;
}