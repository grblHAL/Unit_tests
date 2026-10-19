#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // Set coordinate system
    char block1[] = "G54";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.coord_system == CoordinateSystem_G54);

    // M70 - Save modal state
    char block2[] = "M70";
    CHECK(gc_execute_block(block2) == Status_OK);

    // Change coordinate system
    char block3[] = "G55";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.coord_system == CoordinateSystem_G55);

    // M72 - Restore modal state
    char block4[] = "M72";
    CHECK(gc_execute_block(block4) == Status_OK);

    // Coordinate system should be restored
    CHECK(gc_state.modal.coord_system == CoordinateSystem_G54);

    return EXIT_SUCCESS;
}