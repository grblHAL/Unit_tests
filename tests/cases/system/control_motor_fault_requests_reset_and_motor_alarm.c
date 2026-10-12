#include "support/control_irq_host.h"
#include "check.h"

int main(void)
{
    prepare_control_irq();
    command_controls.motor_fault = true;
    control_interrupt_handler((control_signals_t){.motor_fault=true});
    CHECK(sys.rt_exec_state & EXEC_RESET);
    CHECK(sys.rt_exec_alarm == Alarm_MotorFault);
    CHECK(sys.last_event.control.motor_fault);
    return EXIT_SUCCESS;
}
