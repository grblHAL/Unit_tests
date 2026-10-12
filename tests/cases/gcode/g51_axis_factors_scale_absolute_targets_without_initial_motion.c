#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char move[] = "G0X5Y10Z15";
    CHECK(gc_execute_block(move) == Status_OK);
    char scale[] = "G51X2Y3Z4";
    CHECK(gc_execute_block(scale) == Status_OK);
    NEAR(gc_state.position[0], 5);
    NEAR(gc_state.position[1], 10);
    NEAR(gc_state.position[2], 15);
    char target[] = "G0X2Y3Z4";
    CHECK(gc_execute_block(target) == Status_OK);
    NEAR(gc_state.position[0], 4);
    NEAR(gc_state.position[1], 9);
    NEAR(gc_state.position[2], 16);
    return EXIT_SUCCESS;
}
