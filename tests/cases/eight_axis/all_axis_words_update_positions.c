#include "support/engine_host.h"
#include "check.h"
#include <string.h>
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char block[] = "G1X1Y2Z3A4B5C6U7V8F100";
    CHECK(gc_execute_block(block) == Status_OK);
    CHECK(N_AXIS == 8 && system_n_axis() == 8);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        NEAR(gc_state.position[axis], (float)(axis + 1));
    return EXIT_SUCCESS;
}
