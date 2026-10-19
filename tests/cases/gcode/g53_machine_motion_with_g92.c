#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G92 X10 Y20 - Set G92 offset
    char block1[] = "G92X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.g92_offset[0], -10.0f);
    NEAR(gc_state.g92_offset[1], -20.0f);

    // G0 X0 Y0 - Move to G92 position (machine X10 Y20)
    char block2[] = "G0X0Y0";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 20.0f);

    // G53 G0 X0 Y0 - Move to machine origin (ignores G92 and G54)
    char block3[] = "G53G0X0Y0";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 0.0f);
    NEAR(gc_state.position[1], 0.0f);

    // G0 X0 Y0 - Move back to G92 position
    char block4[] = "G0X0Y0";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 20.0f);

    return EXIT_SUCCESS;
}