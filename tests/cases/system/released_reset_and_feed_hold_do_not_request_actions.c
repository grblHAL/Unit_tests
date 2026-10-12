#include "support/control_irq_host.h"
#include "check.h"

int main(void)
{
    prepare_control_irq();
    control_interrupt_handler((control_signals_t){.reset=true,.feed_hold=true,.deasserted=true});
    CHECK(sys.rt_exec_state == 0);
    CHECK(sys.rt_exec_alarm == Alarm_None);
    CHECK(control_change_calls == 0);
    return EXIT_SUCCESS;
}
