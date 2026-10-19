#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G28.1 X5 Y5 Z5 - Store current position as G28 reference
    char block1[] = "G28.1X5Y5Z5";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G30.1 X10 Y10 Z10 - Store current position as G30 reference
    char block2[] = "G30.1X10Y10Z10";
    CHECK(gc_execute_block(block2) == Status_OK);

    // Move away
    char block3[] = "G0X20Y20Z20";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 20.0f);
    NEAR(gc_state.position[1], 20.0f);
    NEAR(gc_state.position[2], 20.0f);

    // G28 - Return to G28 reference
    char block4[] = "G28";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.position[0], 5.0f);
    NEAR(gc_state.position[1], 5.0f);
    NEAR(gc_state.position[2], 5.0f);

    // G30 - Return to G30 reference
    char block5[] = "G30";
    CHECK(gc_execute_block(block5) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 10.0f);
    NEAR(gc_state.position[2], 10.0f);

    return EXIT_SUCCESS;
}