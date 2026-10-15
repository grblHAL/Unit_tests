#include "support/boot_host.h"
static unsigned callbacks;
static bool plugin_irq(uint_fast8_t id, bool level)
{ (void)id; (void)level; callbacks++; return true; }
int main(void)
{
    CHECK(grbl_enter() == 0);
    CHECK(sys.driver_started && hal.irq_claim != NULL);
    CHECK(!hal.irq_claim(IRQ_SPI, 7, plugin_irq));
    CHECK(callbacks == 0);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
