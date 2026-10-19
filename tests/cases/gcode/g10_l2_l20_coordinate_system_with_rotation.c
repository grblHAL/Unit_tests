#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G10L2P1X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.values[0], 10.0f);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.values[1], 20.0f);
    char block2[] = "G10L2P2X5Y5R90";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(read_saved_coordinate(CoordinateSystem_G55).coord.values[0], 5.0f);
    NEAR(read_saved_coordinate(CoordinateSystem_G55).coord.values[1], 5.0f);
    NEAR(read_saved_coordinate(CoordinateSystem_G55).rotation, 90.0f * RADDEG);
    char block3[] = "G10L20P1X1Y1";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.values[0], -1.0f);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.values[1], -1.0f);
    char block4[] = "G10L2P10X0Y0";
    CHECK(gc_execute_block(block4) == Status_GcodeUnsupportedCoordSys);

    return EXIT_SUCCESS;
}
