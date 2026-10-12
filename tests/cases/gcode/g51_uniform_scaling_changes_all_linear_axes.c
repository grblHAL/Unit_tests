#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char scale[] = "G51X2Y2Z2";
    CHECK(gc_execute_block(scale) == Status_OK);
    CHECK(gc_state.modal.scaling_active);
    for(unsigned axis = 0; axis < 3; axis++) NEAR(gc_get_scaling()[axis], 2);
    char move[] = "G0X1Y2Z3";
    CHECK(gc_execute_block(move) == Status_OK);
    NEAR(gc_state.position[0], 2);
    NEAR(gc_state.position[1], 4);
    NEAR(gc_state.position[2], 6);
    return EXIT_SUCCESS;
}
