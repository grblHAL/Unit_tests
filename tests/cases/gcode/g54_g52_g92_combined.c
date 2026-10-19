#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G54 G10 L2 P1 X10 Y20 - Set G54 offset
    char block1[] = "G10L2P1X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G54 G52 X5 Y5 - Set local offset
    char block2[] = "G54G52X5Y5";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G54 G92 X2 Y2 - Set G92 offset
    char block3[] = "G54G92X2Y2";
    CHECK(gc_execute_block(block3) == Status_OK);

    // G54 G0 X0 Y0 - Move to combined origin
    char block4[] = "G54G0X0Y0";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.position[0], 17.0f); // 10 + 5 + 2
    NEAR(gc_state.position[1], 27.0f); // 20 + 5 + 2

    return EXIT_SUCCESS;
}