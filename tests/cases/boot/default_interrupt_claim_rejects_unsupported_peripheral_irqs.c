#include "support/boot_host.h"

static unsigned callback_calls;
static bool irq_callback(uint_fast8_t id, bool level)
{ (void)id; (void)level; callback_calls++; return true; }

int main(void)
{
    CHECK(grbl_enter() == 0);
    CHECK(hal.irq_claim != NULL);
    CHECK(!hal.irq_claim(IRQ_I2C_Strobe, 0, irq_callback));
    CHECK(!hal.irq_claim(IRQ_SPI, 1, irq_callback));
    CHECK(callback_calls == 0);
    return EXIT_SUCCESS;
}
