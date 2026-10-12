#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char block[] = "G5.1X1Y1I0J1F100";
    CHECK(gc_execute_block(block) == Status_OK);
    NEAR(gc_state.position[X_AXIS], 1);
    NEAR(gc_state.position[Y_AXIS], 1);
    return EXIT_SUCCESS;
}
