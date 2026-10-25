#include "sam_host.h"
int main(void)
{
    sam_prepare();
    for (unsigned n = 0; n < 2; n++)
    {
        sam_mask_clear(n);
        CHECK(sam_stream[n]->disable_rx(false));
        sam_sync();
        CHECK(sam_irq_mask(n) & US_IMR_RXRDY);
        sam_receive(n, 'X');
        CHECK(sam_stream[n]->read() == 'X');
    }
    return 0;
}
