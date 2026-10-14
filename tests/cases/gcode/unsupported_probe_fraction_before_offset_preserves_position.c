#include "support/engine_host.h"
#include "check.h"
static probe_state_t probe_state(void) { return (probe_state_t){0}; }
int main(void)
{
    engine_parser_prepare();
    char move[] = "G0X2Y3Z4";
    CHECK(gc_execute_block(move) == Status_OK);
    hal.probe.get_state = probe_state;
    motion_mode_t previous = gc_state.modal.motion;
    char block[] = "G38.6G92X4F100";
    status_code_t result = gc_execute_block(block);
    CHECK(result == Status_GcodeUnsupportedCommand);
    CHECK(gc_state.modal.motion == previous);
    NEAR(gc_state.position[0], 2); NEAR(gc_state.position[1], 3); NEAR(gc_state.position[2], 4);
    return EXIT_SUCCESS;
}
