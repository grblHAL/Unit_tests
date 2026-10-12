#include "support/control_irq_host.h"
#include "check.h"

int main(void)
{
    prepare_control_irq();
    hal.limits.interrupt_callback = limit_interrupt_handler;
    control_interrupt_handler((control_signals_t){.probe_overtravel=true});
    CHECK(sys.rt_exec_state & EXEC_RESET);
    CHECK(sys.rt_exec_alarm == Alarm_HardLimit);
    CHECK(sys.last_event.limits.min.z);
    CHECK(control_change_calls == 1);
    CHECK(changed_controls.probe_overtravel);
    return EXIT_SUCCESS;
}
