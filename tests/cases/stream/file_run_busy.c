#include "support/engine_host.h"
#include "stream.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    state_set(STATE_IDLE);
    gc_state.file_run = true;
    CHECK(stream_is_busy(false));
    gc_state.file_run = false;
    CHECK(!stream_is_busy(false));
    return EXIT_SUCCESS;
}
