#include "support/engine_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    state_set(STATE_IDLE);
    char block[] = "G51X2E1";
    CHECK(gc_execute_block(block) == Status_GcodeUnusedWords);
    fprintf(stderr, "Rejected G51: active=%u factorX=%g; expected inactive and factor 1\n", gc_state.modal.scaling_active, gc_get_scaling()[X_AXIS]);
    CHECK(!gc_state.modal.scaling_active);
    NEAR(gc_get_scaling()[X_AXIS], 1);
    return EXIT_SUCCESS;
}
