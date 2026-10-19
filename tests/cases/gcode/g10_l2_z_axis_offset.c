#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G10L2P1Z10";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.values[2], 10.0f);
    char block2[] = "G10L2P1X5Y5Z5";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.values[0], 5.0f);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.values[1], 5.0f);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.values[2], 5.0f);
    char block3[] = "G10L2P1A10B20C30";
    CHECK(gc_execute_block(block3) == Status_GcodeNoAxisWords);

    return EXIT_SUCCESS;
}
