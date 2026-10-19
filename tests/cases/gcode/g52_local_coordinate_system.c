#include "support/incoming_gcode_host.h"
int main(void)
{
    prepare_incoming_parser();
    CHECK(incoming_block("G10L2P1X10Y20") == Status_OK);
    CHECK(incoming_block("G92X2Y3") == Status_OK);
    CHECK(incoming_block("G52X5Y5") == Status_GcodeUnsupportedCommand);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    NEAR(read_saved_coordinate(CoordinateSystem_G54).coord.x, 10);
    NEAR(gc_state.g92_offset.coord.x, -12);
    CHECK(incoming_block("G53G0X0Y0") == Status_OK);
    NEAR(gc_state.position[X_AXIS], 0);
    return EXIT_SUCCESS;
}
