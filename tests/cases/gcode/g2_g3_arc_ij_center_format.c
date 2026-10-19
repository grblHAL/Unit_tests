#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G2 X10 Y10 I5 J0 - CW arc to X10 Y10 with center at X5 Y0 (relative)
    char block1[] = "G2X10Y10I5J0F100";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G3 X0 Y10 I-5 J0 - CCW arc to X0 Y10 with center at X-5 Y0
    char block2[] = "G3X0Y10I-5J0F100";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G2 X10 Y0 I0 J5 - CW arc in XY plane
    char block3[] = "G2X10Y0I0J5F100";
    CHECK(gc_execute_block(block3) == Status_OK);

    // G17 G2 Z10 X10 K5 I0 - CW arc in ZX plane
    char block4[] = "G17G2Z10X10K5I0F100";
    CHECK(gc_execute_block(block4) == Status_OK);

    // G18 G2 Y10 Z10 J5 K0 - CW arc in YZ plane
    char block5[] = "G18G2Y10Z10J5K0F100";
    CHECK(gc_execute_block(block5) == Status_OK);

    return EXIT_SUCCESS;
}