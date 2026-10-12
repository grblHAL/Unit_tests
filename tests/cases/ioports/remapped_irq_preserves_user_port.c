#include "support/ioports_host.h"
#include "check.h"
static void interrupted(uint8_t port, bool high) { (void)port; (void)high; }

int main(void)
{
    prepare_ioports();
    CHECK(ioport_remap(Port_Digital, Port_Input, 0, 1));
    CHECK(ioport_enable_irq(0, IRQ_Mode_Change, interrupted));
    CHECK(irq_calls == 1);
    CHECK(irq_physical_port == 1);
    CHECK(irq_user_port == 0);
    CHECK(irq_mode == IRQ_Mode_Change);
    CHECK(irq_callback == interrupted);
    return EXIT_SUCCESS;
}
