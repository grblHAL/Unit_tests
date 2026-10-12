#include "support/engine_host.h"
#include "check.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char block[] = "G20G1U1V1W1F100";
    CHECK(gc_execute_block(block) == Status_OK);
    for(unsigned axis = 3; axis < N_AXIS; axis++)
        NEAR(gc_state.position[axis], 25.4f);
    return EXIT_SUCCESS;
}
