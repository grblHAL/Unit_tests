#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G54 G92 X10 Y20 - Set G54 coordinate system offset
    char block1[] = "G54G92X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.g92_offset[0], -10.0f);
    NEAR(gc_state.g92_offset[1], -20.0f);

    // G55 G92 X5 Y5 - Set G55 coordinate system offset
    char block2[] = "G55G92X5Y5";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.g92_offset[0], -5.0f);
    NEAR(gc_state.g92_offset[1], -5.0f);

    // G92.1 - Reset all G92 offsets
    char block3[] = "G92.1";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.g92_offset[0], 0.0f);
    NEAR(gc_state.g92_offset[1], 0.0f);

    return EXIT_SUCCESS;
}