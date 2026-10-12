#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char offset[] = "G43.1Z5";
    CHECK(gc_execute_block(offset) == Status_OK);
    char cancel[] = "G49";
    CHECK(gc_execute_block(cancel) == Status_OK);
    char move[] = "G0Z1";
    CHECK(gc_execute_block(move) == Status_OK);
    NEAR(gc_state.position[Z_AXIS], 1);
    return EXIT_SUCCESS;
}
