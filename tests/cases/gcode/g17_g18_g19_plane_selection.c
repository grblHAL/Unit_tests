#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G17 - XY plane (default)
    char block1[] = "G17";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);

    // G18 - ZX plane
    char block2[] = "G18";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);

    // G19 - YZ plane
    char block3[] = "G19";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.plane_select == PlaneSelect_YZ);

    // G2/G3 arcs require correct plane
    // G17 G2 X10 Y10 I5 J0 - CW arc in XY plane
    char block4[] = "G17G2X10Y10I5J0F100";
    CHECK(gc_execute_block(block4) == Status_OK);

    // G18 G2 Z10 X10 K5 I0 - CW arc in ZX plane
    char block5[] = "G18G2Z10X10K5I0F100";
    CHECK(gc_execute_block(block5) == Status_OK);

    // G19 G2 Y10 Z10 J5 K0 - CW arc in YZ plane
    char block6[] = "G19G2Y10Z10J5K0F100";
    CHECK(gc_execute_block(block6) == Status_OK);

    return EXIT_SUCCESS;
}