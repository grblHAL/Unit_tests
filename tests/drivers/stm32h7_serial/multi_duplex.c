#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_triplex_prepare();
    const char *tx[] = {"one\n", "two\n", "three\n"};
    const char *rx[] = {"G1X1\n", "$I\n", "M2\n"};
    for (unsigned n = 0; n < 3; n++)
    {
        stmh7_port_stream[n]->write(tx[n]);
        for (const char *s = rx[n]; *s; s++)
            stmh7_receive_port(n, *s);
    }
    for (unsigned n = 0; n < 3; n++)
    {
        stmh7_drain_port(n);
        CHECK(stmh7_port_sent_count[n] == strlen(tx[n]) &&
              !memcmp(stmh7_port_sent[n], tx[n], strlen(tx[n])));
        for (const char *s = rx[n]; *s; s++)
            CHECK(stmh7_port_stream[n]->read() == *s);
        CHECK(stmh7_port_stream[n]->read() == SERIAL_NO_DATA);
    }
    return 0;
}
