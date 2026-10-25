#include "sam_host.h"
int main(void)
{
    sam_prepare();
    sam_allow_blocking = true;
    for (unsigned n = 0; n < 2; n++)
    {
        sam_busy(n, true);
        for (unsigned i = 0; i < 2 * TX_BUFFER_SIZE + 3; i++)
            CHECK(sam_stream[n]->write_char('A' + i % 26));
        sam_drain(n);
        CHECK(sam_sent_count[n] == 2 * TX_BUFFER_SIZE + 3);
        for (unsigned i = 0; i < sam_sent_count[n]; i++)
            CHECK(sam_sent[n][i] == 'A' + (int)(i % 26));
    }
    CHECK(sam_block_calls > 0);
    return 0;
}
