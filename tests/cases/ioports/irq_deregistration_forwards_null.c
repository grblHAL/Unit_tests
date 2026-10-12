#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    CHECK(ioport_enable_irq(1, IRQ_Mode_None, NULL));
    CHECK(irq_calls == 1);
    CHECK(irq_physical_port == 1);
    CHECK(irq_mode == IRQ_Mode_None);
    CHECK(irq_callback == NULL);
    return EXIT_SUCCESS;
}
