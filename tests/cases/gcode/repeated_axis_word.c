#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char block[] = "G1F100X1X2";
    CHECK(gc_execute_block(block) == Status_GcodeWordRepeated); NEAR(gc_state.position[0], 0);
    return EXIT_SUCCESS;
}
