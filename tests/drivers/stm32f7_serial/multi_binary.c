#include "stm7_serial_host.h"
int main(void)
{
    stm7_triplex_prepare();
    const uint8_t data[] = {0, 0x80, 0xff, 'G', '\n'};
    for (unsigned n = 0; n < 3; n++)
        stm7_port_stream[n]->write_n(data, sizeof(data));
    for (unsigned n = 0; n < 3; n++)
    {
        stm7_drain_port(n);
        CHECK(stm7_port_sent_count[n] == sizeof(data) &&
              !memcmp(stm7_port_sent[n], data, sizeof(data)));
    }
    return 0;
}
