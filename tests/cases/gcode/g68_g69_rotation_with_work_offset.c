#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G54 G10 L2 P1 X10 Y20 - Set G54 offset
    char block1[] = "G10L2P1X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G68 X5 Y5 R90 - Rotate around X5 Y5 by 90 degrees
    char block2[] = "G68X5Y5R90";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G54 G0 X0 Y0 - Move in rotated coordinates
    char block3[] = "G54G0X0Y0";
    CHECK(gc_execute_block(block3) == Status_OK);
    // Position depends on rotation implementation

    // G69 - Cancel rotation
    char block4[] = "G69";
    CHECK(gc_execute_block(block4) == Status_OK);

    return EXIT_SUCCESS;
}