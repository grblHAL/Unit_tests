#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G51X0Y0P2";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.modal.scale_factor.ijk.values[0], 2.0f);
    NEAR(gc_state.modal.scale_factor.xyz.values[0], 0.0f);
    NEAR(gc_state.modal.scale_factor.xyz.values[1], 0.0f);
    char block2[] = "G1X10Y10F100";
    CHECK(gc_execute_block(block2) == Status_OK);
    char block3[] = "G50";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.modal.scale_factor.ijk.values[0], 1.0f);

    return EXIT_SUCCESS;
}
