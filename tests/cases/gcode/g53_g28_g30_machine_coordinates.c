#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G28.1 X5 Y5 - Store reference
    char block1[] = "G28.1X5Y5";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G53 G28 X0 Y0 - Machine coordinate reference return
    // Should go to machine origin, not reference
    char block2[] = "G53G28X0Y0";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.position[0], 0.0f);
    NEAR(gc_state.position[1], 0.0f);

    // G28 X0 Y0 - Normal reference return
    char block3[] = "G28X0Y0";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 5.0f);
    NEAR(gc_state.position[1], 5.0f);

    // G53 G30 X0 Y0 - Machine coordinate G30 return
    // G30.1 not set, so should go to machine origin
    char block4[] = "G53G30X0Y0";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.position[0], 0.0f);
    NEAR(gc_state.position[1], 0.0f);

    return EXIT_SUCCESS;
}