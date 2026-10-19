#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G94 - Feed per minute (default)
    char block1[] = "G94";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMinute);

    // G95 - Feed per revolution (requires spindle with encoder)
    char block2[] = "G95";
    CHECK(gc_execute_block(block2) == Status_GcodeUnsupportedCommand); // No spindle encoder

    // G94 G1 X10 F100 - Feed per minute
    char block3[] = "G94G1X10F100";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.feed_rate, 100.0f);

    return EXIT_SUCCESS;
}