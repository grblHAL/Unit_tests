#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G94";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMin);
    char block2[] = "G95";
    CHECK(gc_execute_block(block2) == Status_GcodeUnsupportedCommand);
    char block3[] = "G94G1X10F100";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.feed_rate, 100.0f);

    return EXIT_SUCCESS;
}
