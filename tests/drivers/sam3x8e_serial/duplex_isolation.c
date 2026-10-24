#include "sam_host.h"
int main(void)
{
    sam_prepare();
    const char *tx[] = {"G1X10F200\n", "$I\n"};
    const char *rx[] = {"ok\n", "error:1\n"};
    for (unsigned n = 0; n < 2; n++)
    {
        sam_busy(n, true);
        sam_stream[n]->write(tx[n]);
    }
    for (unsigned n = 0; n < 2; n++)
        for (const char *s = rx[n]; *s; s++)
            sam_receive(n, (uint8_t)*s);
    for (unsigned n = 0; n < 2; n++)
        CHECK(sam_stream[n]->get_rx_buffer_count() == strlen(rx[n]));
    sam_drain(0);
    CHECK(sam_sent_count[0] == strlen(tx[0]) && memcmp(sam_sent[0], tx[0], strlen(tx[0])) == 0 &&
          sam_sent_count[1] == 0);
    CHECK(sam_stream[1]->get_tx_buffer_count() >= strlen(tx[1]));
    for (const char *s = rx[0]; *s; s++)
        CHECK(sam_stream[0]->read() == *s);
    CHECK(sam_stream[0]->read() == SERIAL_NO_DATA &&
          sam_stream[1]->get_rx_buffer_count() == strlen(rx[1]));
    sam_drain(1);
    CHECK(sam_sent_count[1] == strlen(tx[1]) && memcmp(sam_sent[1], tx[1], strlen(tx[1])) == 0);
    for (const char *s = rx[1]; *s; s++)
        CHECK(sam_stream[1]->read() == *s);
    CHECK(sam_stream[1]->read() == SERIAL_NO_DATA && sam_stream[0]->get_tx_buffer_count() == 0 &&
          sam_stream[1]->get_tx_buffer_count() == 0);
    return 0;
}
