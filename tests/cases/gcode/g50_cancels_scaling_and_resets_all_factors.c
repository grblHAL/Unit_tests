#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char scale[] = "G51X2Y2Z2";
    CHECK(gc_execute_block(scale) == Status_OK);
    char cancel[] = "G50";
    CHECK(gc_execute_block(cancel) == Status_OK);
    CHECK(!gc_state.modal.scaling_active);
    for(unsigned axis = 0; axis < N_AXIS; axis++) NEAR(gc_get_scaling()[axis], 1);
    char move[] = "G0X1";
    CHECK(gc_execute_block(move) == Status_OK);
    NEAR(gc_state.position[X_AXIS], 1);
    return EXIT_SUCCESS;
}
