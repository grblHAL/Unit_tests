#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_prepare();
    for (unsigned i = 0; i < TX_BUFFER_SIZE - 1; i++)
        CHECK(stmh7_stream->write_char('A' + i % 26));
    CHECK(!stmh7_stream->write_char('z') && stmh7_block_calls == 1);
    stmh7_drain();
    CHECK(stmh7_sent_count == TX_BUFFER_SIZE - 1);
    for (unsigned i = 0; i < stmh7_sent_count; i++)
        CHECK(stmh7_sent[i] == 'A' + i % 26);
    stmh7_allow_blocking = true;
    for (unsigned i = 0; i < TX_BUFFER_SIZE + 3; i++)
        CHECK(stmh7_stream->write_char('a' + i % 26));
    stmh7_drain();
    CHECK(stmh7_sent_count == 2 * TX_BUFFER_SIZE + 2 && stmh7_block_calls > 1);
    for (unsigned i = 0; i < TX_BUFFER_SIZE + 3; i++)
        CHECK(stmh7_sent[TX_BUFFER_SIZE - 1 + i] == 'a' + i % 26);
    return 0;
}
