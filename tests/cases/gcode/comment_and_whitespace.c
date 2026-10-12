#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char block[] = " g0 x10 (comment) y5 ; ignored X999";
    CHECK(gc_execute_block(block) == Status_OK); NEAR(gc_state.position[0], 10); NEAR(gc_state.position[1], 5);
    return EXIT_SUCCESS;
}
