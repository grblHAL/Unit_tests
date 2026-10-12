#include "support/engine_host.h"
#include "protocol.h"
#include "probe.h"
#include "check.h"
static unsigned toggle_calls;
static void (*original_toggle)(void);
static bool read_input(void *data) { return *(bool *)data; }
static void count_toggle(void) { toggle_calls++; original_toggle(); }
int main(void)
{
    engine_prepare();
    sys.driver_started = true;
    bool input = false;
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_None, &input, read_input));
    original_toggle = hal.probe.connected_toggle;
    hal.probe.connected_toggle = count_toggle;
    CHECK(protocol_enqueue_realtime_command(CMD_PROBE_CONNECTED_TOGGLE));
    CHECK(protocol_enqueue_realtime_command(CMD_PROBE_CONNECTED_TOGGLE));
    CHECK(toggle_calls == 0);
    engine_execute_tasks(STATE_IDLE);
    CHECK(toggle_calls == 2);
    CHECK(hal.probe.get_state().connected);
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
