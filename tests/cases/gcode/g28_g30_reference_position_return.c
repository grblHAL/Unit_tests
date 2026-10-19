#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // Set G28 position
    char block1[] = "G28.1X5Y5";
    CHECK(gc_execute_block(block1) == Status_OK);

    // Move away
    char block2[] = "G0X10Y10";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 10.0f);

    // G28 - Return to G28 position
    char block3[] = "G28";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 5.0f);
    NEAR(gc_state.position[1], 5.0f);

    // G30.1 - Set G30 position
    char block4[] = "G30.1X15Y15";
    CHECK(gc_execute_block(block4) == Status_OK);

    // G30 - Return to G30 position
    char block5[] = "G30";
    CHECK(gc_execute_block(block5) == Status_OK);
    NEAR(gc_state.position[0], 15.0f);
    NEAR(gc_state.position[1], 15.0f);

    return EXIT_SUCCESS;
}