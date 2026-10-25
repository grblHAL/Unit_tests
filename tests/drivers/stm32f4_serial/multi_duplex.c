#include "stm_serial_host.h"
int main(void)
{
    stm_triplex_prepare();
    const char *tx[] = {"one\n", "two\n", "three\n"};
    const char *rx[] = {"G1X1\n", "$I\n", "M2\n"};
    for (unsigned n = 0; n < 3; n++)
    {
        stm_port_stream[n]->write(tx[n]);
        for (const char *s = rx[n]; *s; s++)
            stm_receive_port(n, *s);
    }
    for (unsigned n = 0; n < 3; n++)
    {
        stm_drain_port(n);
        CHECK(stm_port_sent_count[n] == strlen(tx[n]) &&
              !memcmp(stm_port_sent[n], tx[n], strlen(tx[n])));
        for (const char *s = rx[n]; *s; s++)
            CHECK(stm_port_stream[n]->read() == *s);
        CHECK(stm_port_stream[n]->read() == SERIAL_NO_DATA);
    }
    return 0;
}
