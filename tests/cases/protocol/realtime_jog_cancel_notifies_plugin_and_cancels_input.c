#include "support/engine_host.h"
#include "protocol.h"
#include "state_machine.h"
#include "check.h"
static unsigned cancel_calls, jog_cancel_calls;
static void cancel_input(void) { cancel_calls++; }
static void jog_cancelled(sys_state_t state) { CHECK(state == state_get()); jog_cancel_calls++; }
int main(void)
{
    engine_prepare();
    hal.stream.cancel_read_buffer = cancel_input;
    grbl.on_jog_cancel = jog_cancelled;
    CHECK(protocol_enqueue_realtime_command(CMD_JOG_CANCEL));
    CHECK(cancel_calls == 1);
    CHECK(jog_cancel_calls == 1);
    return EXIT_SUCCESS;
}
