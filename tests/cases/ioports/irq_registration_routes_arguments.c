#include "support/ioports_host.h"
#include "check.h"
static void interrupted(uint8_t port, bool high) { (void)port; (void)high; }

int main(void)
{
    prepare_ioports();
    CHECK(ioport_enable_irq(1, IRQ_Mode_Rising, interrupted));
    CHECK(irq_calls == 1);
    CHECK(irq_physical_port == 1 && irq_user_port == 1);
    CHECK(irq_mode == IRQ_Mode_Rising);
    CHECK(irq_callback == interrupted);
    return EXIT_SUCCESS;
}
