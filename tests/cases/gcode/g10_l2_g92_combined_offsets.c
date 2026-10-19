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
    char block2[] = "G92X5Y5";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.g92_offset.coord.values[0], -15.0f);
    NEAR(gc_state.g92_offset.coord.values[1], -25.0f);
    char block3[] = "G0X0Y0";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], -5.0f);
    NEAR(gc_state.position[1], -5.0f);
    char block4[] = "G92.1";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.g92_offset.coord.values[0], 0.0f);
    NEAR(gc_state.g92_offset.coord.values[1], 0.0f);
    char block5[] = "G0X0Y0";
    CHECK(gc_execute_block(block5) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 20.0f);

    return EXIT_SUCCESS;
}
