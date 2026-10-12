#include "support/control_irq_host.h"
#include "check.h"
static unsigned reset_calls;
static void reset_notified(void) { reset_calls++; }
int main(void)
{
    prepare_control_irq();
    grbl.on_reset = reset_notified;
    control_interrupt_handler((control_signals_t){.reset=true,.feed_hold=true});
    control_interrupt_handler((control_signals_t){.reset=true});
    CHECK(sys.rt_exec_state & EXEC_RESET);
    CHECK(!(sys.rt_exec_state & EXEC_FEED_HOLD));
    CHECK(reset_calls == 1);
    CHECK(control_change_calls == 0);
    return EXIT_SUCCESS;
}
