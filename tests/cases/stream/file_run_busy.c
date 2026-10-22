#include "support/engine_host.h"
#include "stream.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    state_set(STATE_IDLE);
    HOST_PARSER_FLAGS.file_run = true;
    CHECK(stream_is_busy(false));
    HOST_PARSER_FLAGS.file_run = false;
    CHECK(!stream_is_busy(false));
    return EXIT_SUCCESS;
}
