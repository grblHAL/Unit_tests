#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G2X10Y10I5J5F100";
    CHECK(gc_execute_block(block1) == Status_OK);
    char block2[] = "G3X0Y10I-5J0F100";
    CHECK(gc_execute_block(block2) == Status_OK);
    char block3[] = "G2X10Y0I5J-5F100";
    CHECK(gc_execute_block(block3) == Status_OK);
    char block4[] = "G18G2X20Z10I5K5F100";
    CHECK(gc_execute_block(block4) == Status_OK);
    char block5[] = "G19G2Y10Z20J5K5F100";
    CHECK(gc_execute_block(block5) == Status_OK);

    return EXIT_SUCCESS;
}
