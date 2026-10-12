#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(!ioport_enable_irq(2, IRQ_Mode_Change, NULL));
    return EXIT_SUCCESS;
}
