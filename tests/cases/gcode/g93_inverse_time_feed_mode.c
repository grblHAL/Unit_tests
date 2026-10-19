#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G93";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.feed_mode == FeedMode_InverseTime);
    char block2[] = "G1X10F2.0";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.feed_rate, 2.0f);
    char block3[] = "G94";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMin);
    char block4[] = "G95";
    CHECK(gc_execute_block(block4) == Status_GcodeUnsupportedCommand);

    return EXIT_SUCCESS;
}
