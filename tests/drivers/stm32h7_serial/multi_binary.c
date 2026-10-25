#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_triplex_prepare();
    const uint8_t data[] = {0, 0x80, 0xff, 'G', '\n'};
    for (unsigned n = 0; n < 3; n++)
        stmh7_port_stream[n]->write_n(data, sizeof(data));
    for (unsigned n = 0; n < 3; n++)
    {
        stmh7_drain_port(n);
        CHECK(stmh7_port_sent_count[n] == sizeof(data) &&
              !memcmp(stmh7_port_sent[n], data, sizeof(data)));
    }
    return 0;
}
