#include "support/incoming_gcode_host.h"
int main(void)
{
    prepare_incoming_parser();
    CHECK(incoming_block("G51X0Y0P2") == Status_OK);
    CHECK(incoming_block("G0X10Y10") == Status_OK);
    NEAR(gc_state.position[X_AXIS], 20);
    NEAR(gc_state.position[Y_AXIS], 20);
    CHECK(incoming_block("G50") == Status_OK);
    CHECK(incoming_block("G53G0X10Y10") == Status_OK);
    NEAR(gc_state.position[X_AXIS], 10);
    NEAR(gc_state.position[Y_AXIS], 10);
    return EXIT_SUCCESS;
}
