#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char initial[] = "G0X5Y10Z15";
    CHECK(gc_execute_block(initial) == Status_OK);
    char scale[] = "G51X2Y2Z2";
    CHECK(gc_execute_block(scale) == Status_OK);
    char move[] = "G91G0X1Y2Z3";
    CHECK(gc_execute_block(move) == Status_OK);
    NEAR(gc_state.position[0], 7);
    NEAR(gc_state.position[1], 14);
    NEAR(gc_state.position[2], 21);
    return EXIT_SUCCESS;
}
