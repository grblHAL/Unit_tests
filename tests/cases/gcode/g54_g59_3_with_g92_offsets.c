#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G54 G10 L2 P1 X10 Y20 - Set G54 offset
    char block1[] = "G10L2P1X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G55 G10 L2 P2 X5 Y5 - Set G55 offset
    char block2[] = "G10L2P2X5Y5";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G54 G92 X2 Y2 - Set G92 offset in G54
    char block3[] = "G54G92X2Y2";
    CHECK(gc_execute_block(block3) == Status_OK);

    // G55 G92 X1 Y1 - Set G92 offset in G55
    char block4[] = "G55G92X1Y1";
    CHECK(gc_execute_block(block4) == Status_OK);

    // G54 G0 X0 Y0 - Move to G54+G92 origin
    char block5[] = "G54G0X0Y0";
    CHECK(gc_execute_block(block5) == Status_OK);
    NEAR(gc_state.position[0], 12.0f); // 10 + 2
    NEAR(gc_state.position[1], 22.0f); // 20 + 2

    // G55 G0 X0 Y0 - Move to G55+G92 origin
    char block6[] = "G55G0X0Y0";
    CHECK(gc_execute_block(block6) == Status_OK);
    NEAR(gc_state.position[0], 6.0f); // 5 + 1
    NEAR(gc_state.position[1], 6.0f); // 5 + 1

    // G92.1 - Reset all G92 offsets
    char block7[] = "G92.1";
    CHECK(gc_execute_block(block7) == Status_OK);

    // G54 G0 X0 Y0 - Move to G54 origin only
    char block8[] = "G54G0X0Y0";
    CHECK(gc_execute_block(block8) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 20.0f);

    return EXIT_SUCCESS;
}