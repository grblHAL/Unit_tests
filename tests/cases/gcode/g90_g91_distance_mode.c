#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G90";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.distance_incremental == false);
    char block2[] = "G91";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(gc_state.modal.distance_incremental == true);
    char block3[] = "G90G0X10";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    char block4[] = "G91G0X5";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.position[0], 15.0f);
    char block5[] = "G90G0X0";
    CHECK(gc_execute_block(block5) == Status_OK);
    NEAR(gc_state.position[0], 0.0f);

    return EXIT_SUCCESS;
}
