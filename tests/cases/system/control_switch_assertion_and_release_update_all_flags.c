#include "support/control_irq_host.h"
#include "check.h"

int main(void)
{
    prepare_control_irq();
    control_interrupt_handler((control_signals_t){.block_delete=true,.single_block=true,.stop_disable=true});
    CHECK(sys.flags.block_delete_enabled && sys.flags.single_block && sys.flags.optional_stop_disable);
    control_interrupt_handler((control_signals_t){.block_delete=true,.single_block=true,.stop_disable=true,.deasserted=true});
    CHECK(!sys.flags.block_delete_enabled && !sys.flags.single_block && !sys.flags.optional_stop_disable);
    CHECK(control_change_calls == 2);
    CHECK(changed_controls.deasserted);
    return EXIT_SUCCESS;
}
