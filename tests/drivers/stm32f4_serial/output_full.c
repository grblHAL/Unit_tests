#include "stm_serial_host.h"
int main(void)
{
    stm_serial_prepare();
    for (unsigned i = 0; i < TX_BUFFER_SIZE - 1; i++)
        CHECK(stm_stream->write_char('A' + i % 26));
    CHECK(!stm_stream->write_char('z') && stm_block_calls == 1);
    stm_drain();
    CHECK(stm_sent_count == TX_BUFFER_SIZE - 1);
    for (unsigned i = 0; i < stm_sent_count; i++)
        CHECK(stm_sent[i] == 'A' + i % 26);
    stm_allow_blocking = true;
    for (unsigned i = 0; i < TX_BUFFER_SIZE + 3; i++)
        CHECK(stm_stream->write_char('a' + i % 26));
    stm_drain();
    CHECK(stm_sent_count == 2 * TX_BUFFER_SIZE + 2 && stm_block_calls > 1);
    for (unsigned i = 0; i < TX_BUFFER_SIZE + 3; i++)
        CHECK(stm_sent[TX_BUFFER_SIZE - 1 + i] == 'a' + i % 26);
    return 0;
}
