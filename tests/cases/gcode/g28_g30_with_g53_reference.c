#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G28.1 X5 Y5 - Store reference position
    char block1[] = "G28.1X5Y5";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G28 X0 Y0 - Return to reference position (machine X5 Y5)
    char block2[] = "G28X0Y0";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.position[0], 5.0f);
    NEAR(gc_state.position[1], 5.0f);

    // G53 G28 X0 Y0 - Machine coordinate reference return
    // G53 makes the following move in machine coordinates
    char block3[] = "G53G28X0Y0";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 0.0f); // Machine origin
    NEAR(gc_state.position[1], 0.0f);

    // G30.1 X10 Y10 - Store G30 reference
    char block4[] = "G30.1X10Y10";
    CHECK(gc_execute_block(block4) == Status_OK);

    // G30 X0 Y0 - Return to G30 reference
    char block5[] = "G30X0Y0";
    CHECK(gc_execute_block(block5) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 10.0f);

    return EXIT_SUCCESS;
}