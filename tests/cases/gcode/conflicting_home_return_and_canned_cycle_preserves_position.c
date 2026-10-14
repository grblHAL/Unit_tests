#include "support/engine_host.h"
#include "check.h"
int main(void)
{
    engine_parser_prepare();
    char move[] = "G0X2Y3Z4";
    CHECK(gc_execute_block(move) == Status_OK);
    motion_mode_t previous = gc_state.modal.motion;
    char block[] = "G30G81X4Z-1R1F100";
    CHECK(gc_execute_block(block) == Status_GcodeAxisCommandConflict);
    CHECK(gc_state.modal.motion == previous);
    NEAR(gc_state.position[0], 2); NEAR(gc_state.position[1], 3); NEAR(gc_state.position[2], 4);
    return EXIT_SUCCESS;
}
