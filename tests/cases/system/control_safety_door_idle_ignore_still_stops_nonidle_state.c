#include "support/control_irq_host.h"
#include "check.h"

int main(void)
{
    prepare_control_irq();
    hal.signals_cap.safety_door_ajar = true;
    settings.safety_door.flags.ignore_when_idle = true;
    control_interrupt_handler((control_signals_t){.safety_door_ajar=true});
    CHECK(!(sys.rt_exec_state & EXEC_SAFETY_DOOR));
    state_set(STATE_HOMING);
    CHECK(state_get() == STATE_HOMING);
    control_interrupt_handler((control_signals_t){.safety_door_ajar=true});
    CHECK(sys.rt_exec_state & EXEC_SAFETY_DOOR);
    return EXIT_SUCCESS;
}
