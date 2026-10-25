#include "sam_host.h"
int main(void)
{
    sam_prepare();
    for (unsigned n = 0; n < 2; n++)
    {
        sam_busy(n, true);
        for (unsigned i = 0; i < TX_BUFFER_SIZE - 1; i++)
            CHECK(sam_stream[n]->write_char('A' + i % 26));
        CHECK(!sam_stream[n]->write_char('z'));
        sam_drain(n);
        CHECK(sam_sent_count[n] == TX_BUFFER_SIZE - 1);
        for (unsigned i = 0; i < TX_BUFFER_SIZE - 1; i++)
            CHECK(sam_sent[n][i] == 'A' + (int)(i % 26));
    }
    CHECK(sam_block_calls == 2);
    return 0;
}
