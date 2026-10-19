#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G93 - Inverse time feed mode
    char block1[] = "G93";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.feed_mode == FeedMode_InverseTime);

    // G1 X10 F2.0 - Feed rate is 1/F = 0.5 minutes per unit
    char block2[] = "G1X10F2.0";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.feed_rate, 0.5f); // Inverse time: feed_rate = 1/F

    // G94 - Return to feed per minute mode
    char block3[] = "G94";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMinute);

    // G95 - Feed per revolution mode (requires spindle)
    char block4[] = "G95";
    CHECK(gc_execute_block(block4) == Status_GcodeUnsupportedCommand); // No spindle data

    return EXIT_SUCCESS;
}