#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G51 X0 Y0 P2 - Scale by factor 2 around X0 Y0
    char block1[] = "G51X0Y0P2";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.modal.scaling.factor, 2.0f);
    NEAR(gc_state.modal.scaling.center[0], 0.0f);
    NEAR(gc_state.modal.scaling.center[1], 0.0f);

    // G1 X10 Y10 - Move in scaled coordinates
    char block2[] = "G1X10Y10F100";
    CHECK(gc_execute_block(block2) == Status_OK);
    // In scaled coordinates, X10 Y10 becomes X20 Y20 in machine coordinates

    // G50 - Cancel scaling
    char block3[] = "G50";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.modal.scaling.factor, 1.0f);

    return EXIT_SUCCESS;
}