#include "support/incoming_gcode_host.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G54";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    char block2[] = "M70";
    CHECK(gc_execute_block(block2) == Status_OK);
    char block3[] = "G55";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G55);
    char block4[] = "M72";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);

    return EXIT_SUCCESS;
}
