#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char block[] = "G4";
    CHECK(gc_execute_block(block) == Status_GcodeValueWordMissing);
    CHECK(gc_state.position[X_AXIS] == 0);
    CHECK(gc_state.position[Y_AXIS] == 0);
    return EXIT_SUCCESS;
}
