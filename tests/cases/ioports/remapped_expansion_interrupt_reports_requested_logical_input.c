#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    CHECK(ioport_remap(Port_Digital, Port_Input, 0, 4));
    CHECK(ioport_enable_irq(0, IRQ_Mode_Change, bank_consumer_irq));
    CHECK(last_bank == 2 && last_local_port == 0 && bank_irq_user_port == 0);
    CHECK(bank_irq_calls == 1 && irq_calls == 0 && bank_irq_mode == IRQ_Mode_Change);
    bank_irq_callback(bank_irq_user_port, true);
    CHECK(bank_received_irq_calls == 1 && bank_received_irq_port == 0 && bank_received_irq_state);
    return EXIT_SUCCESS;
}
