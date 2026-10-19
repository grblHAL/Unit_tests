#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G10L2P1X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);
    char block2[] = "G51X5Y5P2";
    CHECK(gc_execute_block(block2) == Status_OK);
    char block3[] = "G54G0X0Y0";
    CHECK(gc_execute_block(block3) == Status_OK);
    char block4[] = "G50";
    CHECK(gc_execute_block(block4) == Status_OK);

    return EXIT_SUCCESS;
}
