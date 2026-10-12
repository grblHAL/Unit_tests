#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char scale[] = "G51X2Y1";
    CHECK(gc_execute_block(scale) == Status_OK);
    char arc[] = "G3X1Y1I0J1F100";
    CHECK(gc_execute_block(arc) == Status_GcodeInvalidTarget);
    NEAR(gc_state.position[X_AXIS], 0);
    NEAR(gc_state.position[Y_AXIS], 0);
    return EXIT_SUCCESS;
}
