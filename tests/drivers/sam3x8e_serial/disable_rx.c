#include "sam_host.h"
int main(void)
{
    sam_prepare();
    CHECK(sam_irq_mask(SAM_INSTANCE) & US_IMR_RXRDY);
    CHECK(sam_stream[SAM_INSTANCE]->disable_rx(true));
    sam_sync();
    CHECK(!(sam_irq_mask(SAM_INSTANCE) & US_IMR_RXRDY));
    return 0;
}
