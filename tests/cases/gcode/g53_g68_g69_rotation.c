#include "support/incoming_gcode_host.h"
int main(void)
{
    prepare_incoming_parser();
    CHECK(incoming_block("G68X0Y0R90") == Status_GcodeUnsupportedCommand);
    CHECK(incoming_block("G69") == Status_GcodeUnsupportedCommand);
    CHECK(incoming_block("G10L2P1R90") == Status_OK);
    NEAR(gc_state.modal.g5x_offset.data.rotation, 90 * RADDEG);
    CHECK(incoming_block("G0X10Y0") == Status_OK);
    NEAR(gc_state.position[X_AXIS], 0);
    NEAR(gc_state.position[Y_AXIS], 10);
    CHECK(incoming_block("G10L2P1R0") == Status_OK);
    CHECK(incoming_block("G0X10Y0") == Status_OK);
    NEAR(gc_state.position[X_AXIS], 10);
    NEAR(gc_state.position[Y_AXIS], 0);
    return EXIT_SUCCESS;
}
