#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    uint8_t port = 2;
    CHECK(ioport_claim(Port_Digital, Port_Input, &port, "Expansion input") != NULL);
    CHECK(ioports_unclaimed(Port_Digital, Port_Input) == 4);
    CHECK(ioport_enable_irq(port, IRQ_Mode_Rising, bank_consumer_irq));
    CHECK(last_bank == 1 && last_local_port == 0 && bank_irq_user_port == port);
    bank_irq_callback(bank_irq_user_port, true);
    CHECK(bank_received_irq_calls == 1 && bank_received_irq_port == port && bank_received_irq_state);
    return EXIT_SUCCESS;
}
