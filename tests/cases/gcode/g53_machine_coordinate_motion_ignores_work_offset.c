#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // Set G54 offset
    char block1[] = "G10L2P1X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G54 G0 X0 Y0 - Should move to G54 origin (machine X10 Y20)
    char block2[] = "G54G0X0Y0";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 20.0f);

    // G53 G0 X0 Y0 - Should move to machine origin (X0 Y0) ignoring G54
    char block3[] = "G53G0X0Y0";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 0.0f);
    NEAR(gc_state.position[1], 0.0f);

    // G54 G0 X0 Y0 - Should move back to G54 origin
    char block4[] = "G54G0X0Y0";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 20.0f);

    return EXIT_SUCCESS;
}