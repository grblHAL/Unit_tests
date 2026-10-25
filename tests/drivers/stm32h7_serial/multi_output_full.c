#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_triplex_prepare();
    for (unsigned n = 0; n < 3; n++)
    {
        for (unsigned i = 0; i < TX_BUFFER_SIZE - 1; i++)
            CHECK(stmh7_port_stream[n]->write_char('A' + n));
        CHECK(!stmh7_port_stream[n]->write_char('z'));
    }
    CHECK(stmh7_block_calls == 3);
    for (unsigned n = 0; n < 3; n++)
    {
        stmh7_drain_port(n);
        CHECK(stmh7_port_sent_count[n] == TX_BUFFER_SIZE - 1);
        for (unsigned i = 0; i < stmh7_port_sent_count[n]; i++)
            CHECK(stmh7_port_sent[n][i] == 'A' + n);
    }
    stmh7_allow_blocking = true;
    for (unsigned n = 0; n < 3; n++)
    {
        for (unsigned i = 0; i < TX_BUFFER_SIZE + 3; i++)
            CHECK(stmh7_port_stream[n]->write_char('a' + n));
        stmh7_drain_port(n);
        CHECK(stmh7_port_sent_count[n] == 2 * TX_BUFFER_SIZE + 2);
    }
    return 0;
}
