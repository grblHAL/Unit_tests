#include "support/engine_host.h"
#include "protocol.h"
#include "probe.h"
#include "check.h"
static unsigned toggle_calls;
static void count_toggle(void) { toggle_calls++; }
int main(void)
{
    engine_prepare();
    sys.driver_started = true;
    hal.probe.connected_toggle = NULL;
    protocol_enqueue_realtime_command(CMD_PROBE_CONNECTED_TOGGLE);
    hal.probe.connected_toggle = count_toggle;
    engine_execute_tasks(STATE_IDLE);
    CHECK(toggle_calls == 0);
    return EXIT_SUCCESS;
}
