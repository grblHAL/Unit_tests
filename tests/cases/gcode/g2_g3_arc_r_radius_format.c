#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G2 X10 Y10 R5 - CW arc to X10 Y10 with radius 5
    char block1[] = "G2X10Y10R5F100";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G3 X0 Y10 R5 - CCW arc to X0 Y10 with radius 5
    char block2[] = "G3X0Y10R5F100";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G2 X10 Y0 R5 - CW arc
    char block3[] = "G2X10Y0R5F100";
    CHECK(gc_execute_block(block3) == Status_OK);

    // G3 X0 Y0 R5 - CCW arc (full circle)
    char block4[] = "G3X0Y0R5F100";
    CHECK(gc_execute_block(block4) == Status_OK);

    // Negative radius - larger arc
    char block5[] = "G2X10Y10R-5F100";
    CHECK(gc_execute_block(block5) == Status_OK);

    return EXIT_SUCCESS;
}