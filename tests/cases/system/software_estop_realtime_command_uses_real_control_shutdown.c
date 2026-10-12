#include "support/control_irq_host.h"
#include "check.h"

int main(void)
{
    prepare_control_irq();
    hal.control.interrupt_callback = control_interrupt_handler;
    CHECK(protocol_enqueue_realtime_command(CMD_SOFT_ESTOP));
    CHECK(sys.flags.soft_estop);
    CHECK(sys.rt_exec_state & EXEC_RESET);
    CHECK(sys.rt_exec_alarm == Alarm_EStop);
    return EXIT_SUCCESS;
}
