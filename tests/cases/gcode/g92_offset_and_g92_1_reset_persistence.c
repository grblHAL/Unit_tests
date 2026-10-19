#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G92 X10 Y20 - Set coordinate system offset
    char block1[] = "G92X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.g92_offset[0], -10.0f);
    NEAR(gc_state.g92_offset[1], -20.0f);

    // G0 X0 Y0 - Should move to offset position
    char block2[] = "G0X0Y0";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 20.0f);

    // G92.1 - Reset G92 offset (persistence enabled by default in check mode?)
    // Note: g92_is_volatile is set to true in engine_prepare
    char block3[] = "G92.1";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.g92_offset[0], 0.0f);
    NEAR(gc_state.g92_offset[1], 0.0f);

    // Position should now be at machine coordinates
    NEAR(gc_state.position[0], 0.0f);
    NEAR(gc_state.position[1], 0.0f);

    return EXIT_SUCCESS;
}