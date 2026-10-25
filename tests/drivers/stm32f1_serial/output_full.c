#include "stm1_serial_host.h"
int main(void)
{
    stm1_prepare();
    for (unsigned i = 0; i < TX_BUFFER_SIZE - 1; i++)
        CHECK(stm1_stream->write_char('A' + i % 26));
    CHECK(!stm1_stream->write_char('z') && stm1_block_calls == 1);
    stm1_drain();
    CHECK(stm1_sent_count == TX_BUFFER_SIZE - 1);
    for (unsigned i = 0; i < stm1_sent_count; i++)
        CHECK(stm1_sent[i] == 'A' + i % 26);
    stm1_allow_blocking = true;
    for (unsigned i = 0; i < TX_BUFFER_SIZE + 3; i++)
        CHECK(stm1_stream->write_char('a' + i % 26));
    stm1_drain();
    CHECK(stm1_sent_count == 2 * TX_BUFFER_SIZE + 2 && stm1_block_calls > 1);
    for (unsigned i = 0; i < TX_BUFFER_SIZE + 3; i++)
        CHECK(stm1_sent[TX_BUFFER_SIZE - 1 + i] == 'a' + i % 26);
    return 0;
}
