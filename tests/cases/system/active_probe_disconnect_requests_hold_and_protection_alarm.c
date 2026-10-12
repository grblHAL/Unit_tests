#include "support/control_irq_host.h"
#include "check.h"

int main(void)
{
    prepare_control_irq_cycle();
    sys.probing_state = Probing_Active;
    control_interrupt_handler((control_signals_t){.probe_disconnected=true});
    CHECK(sys.rt_exec_state & EXEC_FEED_HOLD);
    CHECK(sys.alarm_pending == Alarm_ProbeProtect);
    CHECK(control_change_calls == 1);
    CHECK(changed_controls.probe_disconnected);
    return EXIT_SUCCESS;
}
