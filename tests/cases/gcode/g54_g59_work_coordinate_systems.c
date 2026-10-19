#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G54 - Work coordinate system 1 (default)
    char block1[] = "G54";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.coord_system == CoordinateSystem_G54);

    // G55 - Work coordinate system 2
    char block2[] = "G55";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(gc_state.modal.coord_system == CoordinateSystem_G55);

    // G56 - Work coordinate system 3
    char block3[] = "G56";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.coord_system == CoordinateSystem_G56);

    // G57 - Work coordinate system 4
    char block4[] = "G57";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(gc_state.modal.coord_system == CoordinateSystem_G57);

    // G58 - Work coordinate system 5
    char block5[] = "G58";
    CHECK(gc_execute_block(block5) == Status_OK);
    CHECK(gc_state.modal.coord_system == CoordinateSystem_G58);

    // G59 - Work coordinate system 6
    char block6[] = "G59";
    CHECK(gc_execute_block(block6) == Status_OK);
    CHECK(gc_state.modal.coord_system == CoordinateSystem_G59);

    // G59.1 - Extended work coordinate system 7
    char block7[] = "G59.1";
    CHECK(gc_execute_block(block7) == Status_OK);
    CHECK(gc_state.modal.coord_system == CoordinateSystem_G59_1);

    // G59.2 - Extended work coordinate system 8
    char block8[] = "G59.2";
    CHECK(gc_execute_block(block8) == Status_OK);
    CHECK(gc_state.modal.coord_system == CoordinateSystem_G59_2);

    // G59.3 - Extended work coordinate system 9
    char block9[] = "G59.3";
    CHECK(gc_execute_block(block9) == Status_OK);
    CHECK(gc_state.modal.coord_system == CoordinateSystem_G59_3);

    return EXIT_SUCCESS;
}