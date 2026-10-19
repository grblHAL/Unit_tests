#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G92 X10 Y20 - Set G92 offset
    char block1[] = "G92X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G68 X0 Y0 R90 - Rotate by 90 degrees
    char block2[] = "G68X0Y0R90";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G0 X0 Y0 - Move in rotated coordinates with G92
    char block3[] = "G0X0Y0";
    CHECK(gc_execute_block(block3) == Status_OK);
    // Position depends on rotation and G92 interaction

    // G69 - Cancel rotation
    char block4[] = "G69";
    CHECK(gc_execute_block(block4) == Status_OK);

    // G92.1 - Cancel G92
    char block5[] = "G92.1";
    CHECK(gc_execute_block(block5) == Status_OK);

    return EXIT_SUCCESS;
}