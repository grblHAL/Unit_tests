#include "support/engine_host.h"
#include "check.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char block[] = "G1A1F100";
    CHECK(gc_execute_block(block) == Status_GcodeUnusedWords);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(gc_state.position[axis] == 0);
    return EXIT_SUCCESS;
}
