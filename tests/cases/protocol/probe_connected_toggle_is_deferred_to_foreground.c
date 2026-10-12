#include "support/engine_host.h"
#include "protocol.h"
#include "probe.h"
#include "check.h"
static bool read_input(void *data) { return *(bool *)data; }
int main(void)
{
    engine_prepare();
    sys.driver_started = true;
    bool input = false;
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_None, &input, read_input));
    CHECK(hal.probe.get_state().connected);
    CHECK(protocol_enqueue_realtime_command(CMD_PROBE_CONNECTED_TOGGLE));
    CHECK(hal.probe.get_state().connected);
    engine_execute_tasks(STATE_IDLE);
    CHECK(!hal.probe.get_state().connected);
    engine_execute_tasks(STATE_IDLE);
    CHECK(!hal.probe.get_state().connected);
    return EXIT_SUCCESS;
}
