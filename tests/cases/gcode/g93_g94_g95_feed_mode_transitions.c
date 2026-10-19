#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // Default is G94 (feed per minute)
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMinute);

    // G93 - Inverse time
    char block1[] = "G93";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.feed_mode == FeedMode_InverseTime);

    // G1 X10 F2 - Feed rate = 1/2 = 0.5 min/unit
    char block2[] = "G1X10F2";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G94 - Back to feed per minute
    char block3[] = "G94";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMinute);

    // G95 - Feed per revolution (requires spindle encoder)
    char block4[] = "G95";
    CHECK(gc_execute_block(block4) == Status_GcodeUnsupportedCommand);

    return EXIT_SUCCESS;
}