#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G10L2P1X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);
    char block2[] = "G10L2P2X5Y5";
    CHECK(gc_execute_block(block2) == Status_OK);
    char block3[] = "G54G92X2Y2";
    CHECK(gc_execute_block(block3) == Status_OK);
    char block4[] = "G55G92X1Y1";
    CHECK(gc_execute_block(block4) == Status_OK);
    char block5[] = "G54G0X0Y0";
    CHECK(gc_execute_block(block5) == Status_OK);
    NEAR(gc_state.position[0], 4.0f);
    NEAR(gc_state.position[1], 14.0f);
    char block6[] = "G55G0X0Y0";
    CHECK(gc_execute_block(block6) == Status_OK);
    NEAR(gc_state.position[0], -1.0f);
    NEAR(gc_state.position[1], -1.0f);
    char block7[] = "G92.1";
    CHECK(gc_execute_block(block7) == Status_OK);
    char block8[] = "G54G0X0Y0";
    CHECK(gc_execute_block(block8) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 20.0f);

    return EXIT_SUCCESS;
}
