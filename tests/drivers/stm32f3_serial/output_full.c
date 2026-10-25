#include "stm3_serial_host.h"
int main(void)
{
    stm3_prepare();
    for (unsigned i = 0; i < TX_BUFFER_SIZE - 1; i++)
        CHECK(stm3_stream->write_char('A' + i % 26));
    CHECK(!stm3_stream->write_char('z') && stm3_block_calls == 1);
    stm3_drain();
    CHECK(stm3_sent_count == TX_BUFFER_SIZE - 1);
    for (unsigned i = 0; i < stm3_sent_count; i++)
        CHECK(stm3_sent[i] == 'A' + i % 26);
    stm3_allow_blocking = true;
    for (unsigned i = 0; i < TX_BUFFER_SIZE + 3; i++)
        CHECK(stm3_stream->write_char('a' + i % 26));
    stm3_drain();
    CHECK(stm3_sent_count == 2 * TX_BUFFER_SIZE + 2 && stm3_block_calls > 1);
    for (unsigned i = 0; i < TX_BUFFER_SIZE + 3; i++)
        CHECK(stm3_sent[TX_BUFFER_SIZE - 1 + i] == 'a' + i % 26);
    return 0;
}
