#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G54";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    char block2[] = "G55";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G55);
    char block3[] = "G56";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G56);
    char block4[] = "G57";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G57);
    char block5[] = "G58";
    CHECK(gc_execute_block(block5) == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G58);
    char block6[] = "G59";
    CHECK(gc_execute_block(block6) == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G59);
    char block7[] = "G59.1";
    CHECK(gc_execute_block(block7) == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G59_1);
    char block8[] = "G59.2";
    CHECK(gc_execute_block(block8) == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G59_2);
    char block9[] = "G59.3";
    CHECK(gc_execute_block(block9) == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G59_3);

    return EXIT_SUCCESS;
}
