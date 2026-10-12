#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char scale[] = "G51";
    CHECK(gc_execute_block(scale) == Status_GcodeNoAxisWords);
    CHECK(!gc_state.modal.scaling_active);
    for(unsigned axis = 0; axis < N_AXIS; axis++) NEAR(gc_get_scaling()[axis], 1);
    return EXIT_SUCCESS;
}
