#include "support/engine_host.h"
#include "check.h"
#include <string.h>
#include <math.h>

int main(void)
{
    engine_parser_prepare();

    // G68 X0 Y0 R90 - Rotate coordinate system 90 degrees around X0 Y0
    char block1[] = "G68X0Y0R90";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.modal.rotation.angle, 90.0f);
    NEAR(gc_state.modal.rotation.center[0], 0.0f);
    NEAR(gc_state.modal.rotation.center[1], 0.0f);

    // G1 X10 Y0 - Move in rotated coordinates
    char block2[] = "G1X10Y0F100";
    CHECK(gc_execute_block(block2) == Status_OK);
    // In rotated coordinates, X10 Y0 becomes Y10 X0 in machine coordinates
    // This depends on the rotation implementation

    // G69 - Cancel rotation
    char block3[] = "G69";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.modal.rotation.angle, 0.0f);

    return EXIT_SUCCESS;
}