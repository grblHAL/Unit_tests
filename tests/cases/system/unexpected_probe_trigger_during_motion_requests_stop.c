#include "support/control_irq_host.h"
#include "check.h"

int main(void)
{
    prepare_control_irq_cycle();
    sys.probing_state = Probing_Off;
    control_interrupt_handler((control_signals_t){.probe_triggered=true});
    CHECK(sys.rt_exec_state & EXEC_STOP);
    CHECK(sys.alarm_pending == Alarm_ProbeProtect);
    CHECK(axis_pulses[X_AXIS] == 0);
    return EXIT_SUCCESS;
}
