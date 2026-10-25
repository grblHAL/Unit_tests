#include "sam_host.h"
int main(void)
{
    sam_prepare();
    const uint8_t binary[] = {0, 0x80, 0xff};
    for (unsigned n = 0; n < 2; n++)
    {
        sam_busy(n, true);
        sam_stream[n]->write("G1X10\n");
        sam_stream[n]->write_n(binary, sizeof(binary));
        sam_sync();
        CHECK(sam_stream[n]->get_tx_buffer_count() == 10);
        sam_drain(n);
        CHECK(sam_sent_count[n] == 9 && !memcmp(sam_sent[n], "G1X10\n", 6) &&
              !memcmp(sam_sent[n] + 6, binary, 3));
        CHECK(!(sam_irq_mask(n) & US_IMR_TXRDY));
    }
    return 0;
}
