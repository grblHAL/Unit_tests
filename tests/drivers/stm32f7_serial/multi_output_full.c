#include "stm7_serial_host.h"
int main(void)
{
    stm7_triplex_prepare();
    for (unsigned n = 0; n < 3; n++)
    {
        for (unsigned i = 0; i < TX_BUFFER_SIZE - 1; i++)
            CHECK(stm7_port_stream[n]->write_char('A' + n));
        CHECK(!stm7_port_stream[n]->write_char('z'));
    }
    CHECK(stm7_block_calls == 3);
    for (unsigned n = 0; n < 3; n++)
    {
        stm7_drain_port(n);
        CHECK(stm7_port_sent_count[n] == TX_BUFFER_SIZE - 1);
        for (unsigned i = 0; i < stm7_port_sent_count[n]; i++)
            CHECK(stm7_port_sent[n][i] == 'A' + n);
    }
    stm7_allow_blocking = true;
    for (unsigned n = 0; n < 3; n++)
    {
        for (unsigned i = 0; i < TX_BUFFER_SIZE + 3; i++)
            CHECK(stm7_port_stream[n]->write_char('a' + n));
        stm7_drain_port(n);
        CHECK(stm7_port_sent_count[n] == 2 * TX_BUFFER_SIZE + 2);
    }
    return 0;
}
