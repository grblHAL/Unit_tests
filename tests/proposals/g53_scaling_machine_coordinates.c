#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G51X0Y0P2";
    CHECK(gc_execute_block(block1) == Status_OK);
    char block2[] = "G53G0X10Y10";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 10.0f);
    char block3[] = "G0X10Y10";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 20.0f);
    NEAR(gc_state.position[1], 20.0f);
    char block4[] = "G50";
    CHECK(gc_execute_block(block4) == Status_OK);

    return EXIT_SUCCESS;
}
