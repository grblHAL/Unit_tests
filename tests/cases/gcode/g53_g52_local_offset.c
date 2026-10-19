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

    // G53 G0 X0 Y0 - Machine coordinate move (ignores G54 and G52)
    char block3[] = "G53G0X0Y0";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 0.0f);
    NEAR(gc_state.position[1], 0.0f);

    // G54 G0 X0 Y0 - Program coordinate move (with G54 and G52)
    char block4[] = "G54G0X0Y0";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.position[0], 15.0f);
    NEAR(gc_state.position[1], 25.0f);

    return EXIT_SUCCESS;
}