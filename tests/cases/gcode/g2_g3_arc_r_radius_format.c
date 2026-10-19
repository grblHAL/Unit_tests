#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G2X10Y10R10F100";
    CHECK(gc_execute_block(block1) == Status_OK);
    char block2[] = "G3X0Y10R5F100";
    CHECK(gc_execute_block(block2) == Status_OK);
    char block3[] = "G2X10Y0R10F100";
    CHECK(gc_execute_block(block3) == Status_OK);
    char block4[] = "G3X0Y0R5F100";
    CHECK(gc_execute_block(block4) == Status_OK);
    char block5[] = "G2X10Y10R-10F100";
    CHECK(gc_execute_block(block5) == Status_OK);

    return EXIT_SUCCESS;
}
