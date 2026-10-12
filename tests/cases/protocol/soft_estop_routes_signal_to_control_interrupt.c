#include "support/engine_host.h"
#include "protocol.h"
#include "check.h"
static unsigned interrupt_calls;
static void control_interrupt(control_signals_t signals) { CHECK(signals.e_stop); CHECK(signals.mask == (control_signals_t){.e_stop=true}.mask); interrupt_calls++; }
int main(void)
{
    engine_prepare();
    hal.control.interrupt_callback = control_interrupt;
    CHECK(protocol_enqueue_realtime_command(CMD_SOFT_ESTOP));
    CHECK(sys.flags.soft_estop);
    CHECK(interrupt_calls == 1);
    return EXIT_SUCCESS;
}
