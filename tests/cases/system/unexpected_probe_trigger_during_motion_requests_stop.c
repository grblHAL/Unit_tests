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
    CHECK(!protocol_exec_rt_system());
    CHECK(state_get() == STATE_ALARM && sys.alarm == Alarm_ProbeProtect);
    CHECK(sys.alarm_pending == Alarm_None);
    CHECK(plan_get_current_block() == NULL);
    CHECK(axis_pulses[X_AXIS] == 0 && sys.position[X_AXIS] == 0);
    CHECK(strstr(engine_output, "ALARM:13") != NULL);
    return EXIT_SUCCESS;
}
