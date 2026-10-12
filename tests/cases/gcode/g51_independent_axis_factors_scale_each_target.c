#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char scale[] = "G51X2Y3Z4";
    CHECK(gc_execute_block(scale) == Status_OK);
    char move[] = "G0X1Y1Z1";
    CHECK(gc_execute_block(move) == Status_OK);
    NEAR(gc_state.position[0], 2);
    NEAR(gc_state.position[1], 3);
    NEAR(gc_state.position[2], 4);
    return EXIT_SUCCESS;
}
