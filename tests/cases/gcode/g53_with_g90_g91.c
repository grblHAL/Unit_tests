#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G10 L2 P1 X10 Y20 - Set G54 offset
    char block1[] = "G10L2P1X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G90 G53 G0 X0 Y0 - Machine coordinate move in absolute mode
    char block2[] = "G90G53G0X0Y0";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.position[0], 0.0f);
    NEAR(gc_state.position[1], 0.0f);

    // G91 G53 G0 X5 Y5 - Machine coordinate move in incremental mode
    // G53 ignores G90/G91
    char block3[] = "G91G53G0X5Y5";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 5.0f);
    NEAR(gc_state.position[1], 5.0f);

    // G90 G0 X0 Y0 - Program coordinate move
    char block4[] = "G90G0X0Y0";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 20.0f);

    return EXIT_SUCCESS;
}