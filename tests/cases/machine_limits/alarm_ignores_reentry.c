#include "support/control_host.h"
#include "check.h"
static uint_fast16_t atomic(volatile uint_fast16_t *value, uint_fast16_t bits) { uint_fast16_t previous = *value; *value = bits; return previous; }
int main(void)
{
    hal.set_value_atomic = atomic; host_state = STATE_ALARM;
    limit_signals_t signals = {.max.mask = 2}; limit_interrupt_handler(signals);
    CHECK(host_reset_calls == 0); CHECK(sys.rt_exec_alarm == 0); CHECK(sys.last_event.limits.max.mask == 2);
    return EXIT_SUCCESS;
}
