#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G51 X0 Y0 P2 - Scale by 2
    char block1[] = "G51X0Y0P2";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G68 X0 Y0 R90 - Rotate by 90 degrees
    char block2[] = "G68X0Y0R90";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G1 X10 Y0 - Move in scaled and rotated coordinates
    char block3[] = "G1X10Y0F100";
    CHECK(gc_execute_block(block3) == Status_OK);

    // G69 - Cancel rotation
    char block4[] = "G69";
    CHECK(gc_execute_block(block4) == Status_OK);

    // G50 - Cancel scaling
    char block5[] = "G50";
    CHECK(gc_execute_block(block5) == Status_OK);

    return EXIT_SUCCESS;
}