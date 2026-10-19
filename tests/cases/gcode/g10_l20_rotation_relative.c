#include "support/incoming_gcode_host.h"
int main(void)
{
    prepare_incoming_parser();
    CHECK(incoming_block("G10L2P1X10Y20R90") == Status_OK);
    CHECK(incoming_block("G10L20P1X5Y5") == Status_OK);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.x, -5);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.y, -5);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).rotation, 90 * RADDEG);
    CHECK(incoming_block("G10L20P1R45") == Status_GcodeNoAxisWords);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).rotation, 90 * RADDEG);
    return EXIT_SUCCESS;
}
