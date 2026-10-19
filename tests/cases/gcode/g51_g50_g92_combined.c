#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G92X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);
    char block2[] = "G51X0Y0P2";
    CHECK(gc_execute_block(block2) == Status_OK);
    char block3[] = "G0X0Y0";
    CHECK(gc_execute_block(block3) == Status_OK);
    char block4[] = "G50";
    CHECK(gc_execute_block(block4) == Status_OK);
    char block5[] = "G92.1";
    CHECK(gc_execute_block(block5) == Status_OK);

    return EXIT_SUCCESS;
}
