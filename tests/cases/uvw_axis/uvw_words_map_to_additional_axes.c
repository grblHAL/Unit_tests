#include "support/engine_host.h"
#include "check.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char block[] = "G1U1V2W3F100";
    CHECK(gc_execute_block(block) == Status_OK);
    CHECK(N_AXIS == 6);
    NEAR(gc_state.position[3], 1);
    NEAR(gc_state.position[4], 2);
    NEAR(gc_state.position[5], 3);
    CHECK(gc_state.position[X_AXIS] == 0);
    return EXIT_SUCCESS;
}
