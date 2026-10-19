#include "support/incoming_gcode_host.h"
int main(void)
{
    prepare_incoming_parser();
    CHECK(incoming_block("G90G10L2P1X10Y20") == Status_OK);
    CHECK(incoming_block("G91G10L2P1X5Y5") == Status_OK);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.x, 5);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.y, 5);
    CHECK(incoming_block("G90G10L20P1X5Y5") == Status_OK);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.x, -5);
    CHECK(incoming_block("G91G10L20P1X5Y5") == Status_OK);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.x, -5);
    return EXIT_SUCCESS;
}
