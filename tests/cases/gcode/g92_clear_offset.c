#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char first[] = "G0X10";
    CHECK(gc_execute_block(first) == Status_OK);
    char offset[] = "G92X2";
    CHECK(gc_execute_block(offset) == Status_OK);
    char clear[] = "G92.1";
    CHECK(gc_execute_block(clear) == Status_OK);
    char next[] = "G0X3";
    CHECK(gc_execute_block(next) == Status_OK);
    NEAR(gc_state.position[X_AXIS], 3);
    return EXIT_SUCCESS;
}
