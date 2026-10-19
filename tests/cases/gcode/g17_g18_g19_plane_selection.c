#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G17";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    char block2[] = "G18";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);
    char block3[] = "G19";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.plane_select == PlaneSelect_YZ);
    char block4[] = "G17G2X10Y10I5J5F100";
    CHECK(gc_execute_block(block4) == Status_OK);
    char block5[] = "G18G2Z10X10K5I0F100";
    CHECK(gc_execute_block(block5) == Status_OK);
    char block6[] = "G19G2Y10Z10J5K0F100";
    CHECK(gc_execute_block(block6) == Status_OK);

    return EXIT_SUCCESS;
}
