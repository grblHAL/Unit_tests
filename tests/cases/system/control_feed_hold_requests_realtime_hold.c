#include "support/control_irq_host.h"
#include "check.h"

int main(void)
{
    prepare_control_irq();
    control_interrupt_handler((control_signals_t){.feed_hold=true});
    CHECK(sys.rt_exec_state == EXEC_FEED_HOLD);
    CHECK(sys.last_event.control.feed_hold);
    CHECK(control_change_calls == 0);
    return EXIT_SUCCESS;
}
