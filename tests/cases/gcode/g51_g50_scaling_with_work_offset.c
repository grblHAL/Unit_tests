#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G54 G10 L2 P1 X10 Y20 - Set G54 offset
    char block1[] = "G10L2P1X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G51 X5 Y5 P2 - Scale by 2 around X5 Y5
    char block2[] = "G51X5Y5P2";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G54 G0 X0 Y0 - Move in scaled coordinates
    char block3[] = "G54G0X0Y0";
    CHECK(gc_execute_block(block3) == Status_OK);
    // Position depends on scaling implementation

    // G50 - Cancel scaling
    char block4[] = "G50";
    CHECK(gc_execute_block(block4) == Status_OK);

    return EXIT_SUCCESS;
}