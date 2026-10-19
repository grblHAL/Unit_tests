#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G10L2P1X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);
    char block2[] = "G54G0X0Y0";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 20.0f);
    char block3[] = "G53G0X0Y0";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 0.0f);
    NEAR(gc_state.position[1], 0.0f);
    char block4[] = "G54G0X0Y0";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 20.0f);

    return EXIT_SUCCESS;
}
