#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G92 X10 Y20 - Set G92 offset
    char block1[] = "G92X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G51 X0 Y0 P2 - Scale by 2
    char block2[] = "G51X0Y0P2";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G0 X0 Y0 - Move in scaled coordinates with G92
    char block3[] = "G0X0Y0";
    CHECK(gc_execute_block(block3) == Status_OK);
    // Position depends on scaling and G92 interaction

    // G50 - Cancel scaling
    char block4[] = "G50";
    CHECK(gc_execute_block(block4) == Status_OK);

    // G92.1 - Cancel G92
    char block5[] = "G92.1";
    CHECK(gc_execute_block(block5) == Status_OK);

    return EXIT_SUCCESS;
}