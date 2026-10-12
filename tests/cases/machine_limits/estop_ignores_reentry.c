#include "support/control_host.h"
#include "check.h"
static uint_fast16_t atomic(volatile uint_fast16_t *value, uint_fast16_t bits) { uint_fast16_t previous = *value; *value = bits; return previous; }
int main(void)
{
    hal.set_value_atomic = atomic; host_state = STATE_ESTOP;
    limit_signals_t signals = {.min.mask = 1}; limit_interrupt_handler(signals);
    CHECK(host_reset_calls == 0); CHECK(sys.rt_exec_alarm == 0);
    return EXIT_SUCCESS;
}
