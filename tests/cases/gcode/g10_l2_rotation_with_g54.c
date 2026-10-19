#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G10L2P1X10Y20R90";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.values[0], 10.0f);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.values[1], 20.0f);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).rotation, 90.0f * RADDEG);
    char block2[] = "G10L2P1X5Y5R45";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.values[0], 5.0f);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.values[1], 5.0f);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).rotation, 45.0f * RADDEG);
    char block3[] = "G10L2P1R0";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).rotation, 0.0f * RADDEG);

    return EXIT_SUCCESS;
}
