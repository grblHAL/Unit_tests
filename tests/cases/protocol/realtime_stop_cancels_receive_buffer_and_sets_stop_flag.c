#include "support/engine_host.h"
#include "protocol.h"
#include "check.h"
static unsigned cancel_calls;
static void cancel_input(void) { cancel_calls++; }
int main(void)
{
    engine_prepare();
    hal.stream.cancel_read_buffer = cancel_input;
    CHECK(protocol_enqueue_realtime_command(CMD_STOP));
    CHECK(cancel_calls == 1);
    CHECK(sys.rt_exec_state == EXEC_STOP);
    return EXIT_SUCCESS;
}
