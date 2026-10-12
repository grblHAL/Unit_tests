#include "support/control_irq_host.h"
#include "check.h"

int main(void)
{
    prepare_control_irq();
    command_controls.e_stop = true;
    control_interrupt_handler((control_signals_t){.e_stop=true});
    CHECK(sys.rt_exec_state & EXEC_RESET);
    CHECK(sys.rt_exec_alarm == Alarm_EStop);
    CHECK(sys.last_event.control.e_stop);
    return EXIT_SUCCESS;
}
