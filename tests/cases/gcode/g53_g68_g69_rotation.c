#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G68 X0 Y0 R90 - Rotate by 90 degrees
    char block1[] = "G68X0Y0R90";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G53 G0 X10 Y10 - Machine coordinate move (ignores rotation)
    char block2[] = "G53G0X10Y10";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 10.0f);

    // G0 X10 Y10 - Program coordinate move (with rotation)
    char block3[] = "G0X10Y10";
    CHECK(gc_execute_block(block3) == Status_OK);
    // Position depends on rotation

    // G69 - Cancel rotation
    char block4[] = "G69";
    CHECK(gc_execute_block(block4) == Status_OK);

    return EXIT_SUCCESS;
}