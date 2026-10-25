#include "stm7_serial_host.h"
int main(void)
{
    stm7_prepare();
    for (unsigned i = 0; i < TX_BUFFER_SIZE - 1; i++)
        CHECK(stm7_stream->write_char('A' + i % 26));
    CHECK(!stm7_stream->write_char('z') && stm7_block_calls == 1);
    stm7_drain();
    CHECK(stm7_sent_count == TX_BUFFER_SIZE - 1);
    for (unsigned i = 0; i < stm7_sent_count; i++)
        CHECK(stm7_sent[i] == 'A' + i % 26);
    stm7_allow_blocking = true;
    for (unsigned i = 0; i < TX_BUFFER_SIZE + 3; i++)
        CHECK(stm7_stream->write_char('a' + i % 26));
    stm7_drain();
    CHECK(stm7_sent_count == 2 * TX_BUFFER_SIZE + 2 && stm7_block_calls > 1);
    for (unsigned i = 0; i < TX_BUFFER_SIZE + 3; i++)
        CHECK(stm7_sent[TX_BUFFER_SIZE - 1 + i] == 'a' + i % 26);
    return 0;
}
