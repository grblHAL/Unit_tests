#include "support/boot_host.h"

static unsigned claims;
static bool irq_callback(uint_fast8_t id, bool level)
{ CHECK(id == 7 && level); return true; }
static bool driver_claim(irq_type_t irq, uint_fast8_t id, irq_callback_ptr callback)
{
    CHECK(irq == IRQ_SPI && id == 7 && callback == irq_callback);
    claims++; return true;
}
static void install_driver_irq(void) { hal.irq_claim = driver_claim; }

int main(void)
{
    boot_during_init = install_driver_irq;
    CHECK(grbl_enter() == 0);
    CHECK(hal.irq_claim == driver_claim);
    CHECK(hal.irq_claim(IRQ_SPI, 7, irq_callback));
    CHECK(claims == 1);
    return EXIT_SUCCESS;
}
