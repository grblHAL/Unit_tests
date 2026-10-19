#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G90 - Absolute distance mode (default)
    char block1[] = "G90";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.distance == DistanceMode_Absolute);

    // G91 - Incremental distance mode
    char block2[] = "G91";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(gc_state.modal.distance == DistanceMode_Incremental);

    // G90 G0 X10 - Absolute move to X10
    char block3[] = "G90G0X10";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);

    // G91 G0 X5 - Incremental move +5 from current position
    char block4[] = "G91G0X5";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.position[0], 15.0f);

    // G90 G0 X0 - Absolute move to X0
    char block5[] = "G90G0X0";
    CHECK(gc_execute_block(block5) == Status_OK);
    NEAR(gc_state.position[0], 0.0f);

    return EXIT_SUCCESS;
}